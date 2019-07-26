#include "touchy.h"
#include <thread>
#include <QFile>
#include <iostream>
#include <QSocketNotifier>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <QGuiApplication>
#include <QTransform>
#include <qwindowsysteminterface.h>
#include <QPointer>
#include <QDebug>
#include <QString>

class QEvdevTouchScreenData
{
public:
    QEvdevTouchScreenData(touchy *q_ptr);

    QString getCodeName(const int &code);

    void processInputEvent(input_event *data);
    void assignIds();

    touchy *q;
    int m_lastEventType;
    QList<QWindowSystemInterface::TouchPoint> m_touchPoints;
    QList<QWindowSystemInterface::TouchPoint> m_lastTouchPoints;

    struct Contact {
        int trackingId;
        int x;
        int y;
        int maj;
        int pressure;
        Qt::TouchPointState state;
        QTouchEvent::TouchPoint::InfoFlags flags;
        Contact() : trackingId(-1),
            x(0), y(0), maj(-1), pressure(0),
            state(Qt::TouchPointPressed), flags(0) { }
    };
    QHash<int, Contact> m_contacts; // The key is a tracking id for type A, slot number for type B.
    QHash<int, Contact> m_lastContacts;
    Contact m_currentData;
    int m_currentSlot;

    double m_timeStamp;
    double m_lastTimeStamp;

    int findClosestContact(const QHash<int, Contact> &contacts, int x, int y, int *dist);
    void addTouchPoint(const Contact &contact, Qt::TouchPointStates *combinedStates);
    void reportPoints();
    void loadMultiScreenMappings();

    QRect screenGeometry() const;

    int hw_range_x_min;
    int hw_range_x_max;
    int hw_range_y_min;
    int hw_range_y_max;
    int hw_pressure_min;
    int hw_pressure_max;
    QString hw_name;
    QString deviceNode;
    bool m_forceToActiveWindow;
    bool m_typeB;
    QTransform m_rotate;
    bool m_singleTouch;
    QString m_screenName;
    mutable QPointer<QScreen> m_screen;

    // Touch filtering and prediction are part of the same thing. The default
    // prediction is 0ms, but sensible results can be acheived by setting it
    // to, for instance, 16ms.
    // For filtering to work well, the QPA plugin should provide a dead-steady
    // implementation of QPlatformWindow::requestUpdate().
    bool m_filtered;
    int m_prediction;

    // When filtering is enabled, protect the access to current and last
    // timeStamp and touchPoints, as these are being read on the gui thread.
    QMutex m_mutex;
};
QEvdevTouchScreenData::QEvdevTouchScreenData(touchy *q_ptr)
    : q(q_ptr),
      m_lastEventType(-1),
      m_currentSlot(0),
      m_timeStamp(0), m_lastTimeStamp(0),
      hw_range_x_min(0), hw_range_x_max(1023),
      hw_range_y_min(0), hw_range_y_max(1023),
      hw_pressure_min(0), hw_pressure_max(1023),
      m_forceToActiveWindow(false), m_typeB(false), m_singleTouch(false),
      m_filtered(false), m_prediction(0)
{
    //    for (const QString &arg : args) {
    //        if (arg == QStringLiteral("force_window"))
    //            m_forceToActiveWindow = true;
    //        else if (arg == QStringLiteral("filtered"))
    //            m_filtered = true;
    //        else if (arg.startsWith(QStringLiteral("prediction=")))
    //            m_prediction = arg.mid(11).toInt();
    //    }
}
touchy::touchy(QObject *parent) : QObject(parent), m_fd(0)
{
    d = new QEvdevTouchScreenData(this);
    const char *input = "/dev/input/touchscreen0";
    m_fd = open(input, O_RDONLY | O_NDELAY);
    QSocketNotifier *m_notify = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
    connect(m_notify, SIGNAL(activated(int)), this, SLOT(run(int)));
    std::cout << "file open: " << m_fd << std::endl;
}

touchy::~touchy()
{
    std::cout << "closing: " << m_fd << std::endl;
    close(m_fd);
}

void touchy::run(int fd)
{
    //    std::cout << "run called: " << fd << std::endl;
    std::thread t([=](int argfd){

        ::input_event buffer[32];
        int events = -1;
        int n = 0;
        for (; ;) {
            events = read(argfd, reinterpret_cast<char*>(buffer) + n, sizeof(buffer) - n);
            if (events <= 0)
                goto err;
            n += events;
            if (n % sizeof(::input_event) == 0)
                break;
        }

        n /= sizeof(::input_event);

        for (int i = 0; i < n; ++i)
        {
            d->processInputEvent(&buffer[i]);
        }


err:
        {
            //                std::cout << "@err" << std::endl;
        }
    }, m_fd);
    t.detach();
}

int QEvdevTouchScreenData::findClosestContact(const QHash<int, Contact> &contacts, int x, int y, int *dist)
{
    int minDist = -1, id = -1;
    for (QHash<int, Contact>::const_iterator it = contacts.constBegin(), ite = contacts.constEnd();
         it != ite; ++it) {
        const Contact &contact(it.value());
        int dx = x - contact.x;
        int dy = y - contact.y;
        int dist = dx * dx + dy * dy;
        if (minDist == -1 || dist < minDist) {
            minDist = dist;
            id = contact.trackingId;
        }
    }
    if (dist)
        *dist = minDist;
    return id;
}

void QEvdevTouchScreenData::assignIds()
{
    QHash<int, Contact> candidates = m_lastContacts, pending = m_contacts, newContacts;
    int maxId = -1;
    QHash<int, Contact>::iterator it, ite, bestMatch;
    while (!pending.isEmpty() && !candidates.isEmpty()) {
        int bestDist = -1, bestId = 0;
        for (it = pending.begin(), ite = pending.end(); it != ite; ++it) {
            int dist;
            int id = findClosestContact(candidates, it->x, it->y, &dist);
            if (id >= 0 && (bestDist == -1 || dist < bestDist)) {
                bestDist = dist;
                bestId = id;
                bestMatch = it;
            }
        }
        if (bestDist >= 0) {
            bestMatch->trackingId = bestId;
            newContacts.insert(bestId, *bestMatch);
            candidates.remove(bestId);
            pending.erase(bestMatch);
            if (bestId > maxId)
                maxId = bestId;
        }
    }
    if (candidates.isEmpty()) {
        for (it = pending.begin(), ite = pending.end(); it != ite; ++it) {
            it->trackingId = ++maxId;
            newContacts.insert(it->trackingId, *it);
        }
    }
    m_contacts = newContacts;
}

QRect QEvdevTouchScreenData::screenGeometry() const
{
    if (m_forceToActiveWindow) {
        QWindow *win = QGuiApplication::focusWindow();
        return QRect(0,0,480,800); /*return window rect here*///win ? QHighDpi::toNativePixels(win->geometry(), win) : QRect();
    }

    // Now it becomes tricky. Traditionally we picked the primaryScreen()
    // and were done with it. But then, enter multiple screens, and
    // suddenly it was all broken.
    //
    // For now we only support the display configuration of the KMS/DRM
    // backends of eglfs. See QTouchOutputMapping.
    //
    // The good news it that once winRect refers to the correct screen
    // geometry in the full virtual desktop space, there is nothing else
    // left to do since qguiapp will handle the rest.
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!m_screenName.isEmpty()) {
        if (!m_screen) {
            const QList<QScreen *> screens = QGuiApplication::screens();
            for (QScreen *s : screens) {
                if (s->name() == m_screenName) {
                    m_screen = s;
                    break;
                }
            }
        }
        if (m_screen)
            screen = m_screen;
    }
    return QRect(0,0,480,800); /*return window rect here*///QHighDpi::toNativePixels(screen->geometry(), screen);
}

void QEvdevTouchScreenData::reportPoints()
{
    QRect winRect = screenGeometry();
    if (winRect.isNull())
        return;

    const int hw_w = hw_range_x_max - hw_range_x_min;
    const int hw_h = hw_range_y_max - hw_range_y_min;

    // Map the coordinates based on the normalized position. QPA expects 'area'
    // to be in screen coordinates.
    const int pointCount = m_touchPoints.count();
    for (int i = 0; i < pointCount; ++i) {
        QWindowSystemInterface::TouchPoint &tp(m_touchPoints[i]);

        // Generate a screen position that is always inside the active window
        // or the primary screen.  Even though we report this as a QRectF, internally
        // Qt uses QRect/QPoint so we need to bound the size to winRect.size() - QSize(1, 1)
        const qreal wx = winRect.left() + tp.normalPosition.x() * (winRect.width() - 1);
        const qreal wy = winRect.top() + tp.normalPosition.y() * (winRect.height() - 1);
        const qreal sizeRatio = (winRect.width() + winRect.height()) / qreal(hw_w + hw_h);
        if (tp.area.width() == -1) // touch major was not provided
            tp.area = QRectF(0, 0, 8, 8);
        else
            tp.area = QRectF(0, 0, tp.area.width() * sizeRatio, tp.area.height() * sizeRatio);
        tp.area.moveCenter(QPointF(wx, wy));

        // Calculate normalized pressure.
        if (!hw_pressure_min && !hw_pressure_max)
            tp.pressure = tp.state == Qt::TouchPointReleased ? 0 : 1;
        else
            tp.pressure = (tp.pressure - hw_pressure_min) / qreal(hw_pressure_max - hw_pressure_min);

        qDebug() << "Touchpoint:: x:" << tp.normalPosition.x() << "; y:" << tp.normalPosition.y() << "; pressure:" << tp.pressure;
    }


    // Let qguiapp pick the target window.
    if (m_filtered){
        qDebug() << "touchPointsUpdated";
        emit q->touchPointsUpdated();
    }
    else {
        qDebug() << "::handleTouchEvent::";
        QWindowSystemInterface::handleTouchEvent(Q_NULLPTR, q->touchDevice(), m_touchPoints);
    }
}
void QEvdevTouchScreenData::addTouchPoint(const Contact &contact, Qt::TouchPointStates *combinedStates)
{
    QWindowSystemInterface::TouchPoint tp;
    tp.id = contact.trackingId;
    tp.flags = contact.flags;
    tp.state = contact.state;
    *combinedStates |= tp.state;

    // Store the HW coordinates for now, will be updated later.
    tp.area = QRectF(0, 0, contact.maj, contact.maj);
    tp.area.moveCenter(QPoint(contact.x, contact.y));
    tp.pressure = contact.pressure;

    // Get a normalized position in range 0..1.
    tp.normalPosition = QPointF((contact.x - hw_range_x_min) / qreal(hw_range_x_max - hw_range_x_min),
                                (contact.y - hw_range_y_min) / qreal(hw_range_y_max - hw_range_y_min));

    if (!m_rotate.isIdentity())
        tp.normalPosition = m_rotate.map(tp.normalPosition);

    tp.rawPositions.append(QPointF(contact.x, contact.y));

    m_touchPoints.append(tp);
}
QString QEvdevTouchScreenData::getCodeName(const int &code)
{
    switch (code) {
    case ABS_X:
        return "0; x";
    case ABS_Y:
        return "1; y";
    case ABS_PRESSURE:
        return "18; pressure";
    default:
        return QString(code);
    }
}
void QEvdevTouchScreenData::processInputEvent(input_event *data)
{

    if (data->type == EV_ABS) {
//        qDebug() << "Code:" << getCodeName(data->code) << ":" << data->value;
        m_singleTouch = true;

        if (data->code == ABS_MT_POSITION_X || (m_singleTouch && data->code == ABS_X)) {
            m_currentData.x = qBound(hw_range_x_min, data->value, hw_range_x_max);
            if (m_singleTouch)
                m_contacts[m_currentSlot].x = m_currentData.x;
            if (m_typeB) {
                m_contacts[m_currentSlot].x = m_currentData.x;
                if (m_contacts[m_currentSlot].state == Qt::TouchPointStationary)
                    m_contacts[m_currentSlot].state = Qt::TouchPointMoved;
            }
        } else if (data->code == ABS_MT_POSITION_Y || (m_singleTouch && data->code == ABS_Y)) {
            m_currentData.y = qBound(hw_range_y_min, data->value, hw_range_y_max);
            if (m_singleTouch)
                m_contacts[m_currentSlot].y = m_currentData.y;
            if (m_typeB) {
                m_contacts[m_currentSlot].y = m_currentData.y;
                if (m_contacts[m_currentSlot].state == Qt::TouchPointStationary)
                    m_contacts[m_currentSlot].state = Qt::TouchPointMoved;
            }
        } else if (data->code == ABS_MT_TRACKING_ID) {
            m_currentData.trackingId = data->value;
            if (m_typeB) {
                if (m_currentData.trackingId == -1) {
                    m_contacts[m_currentSlot].state = Qt::TouchPointReleased;
                } else {
                    m_contacts[m_currentSlot].state = Qt::TouchPointPressed;
                    m_contacts[m_currentSlot].trackingId = m_currentData.trackingId;
                }
            }
        } else if (data->code == ABS_MT_TOUCH_MAJOR) {
            m_currentData.maj = data->value;
            if (data->value == 0)
                m_currentData.state = Qt::TouchPointReleased;
            if (m_typeB)
                m_contacts[m_currentSlot].maj = m_currentData.maj;
        } else if (data->code == ABS_PRESSURE) {
            m_currentData.pressure = qBound(hw_pressure_min, data->value, hw_pressure_max);
            if (m_typeB || m_singleTouch)
                m_contacts[m_currentSlot].pressure = m_currentData.pressure;
        } else if (data->code == ABS_MT_SLOT) {
            m_currentSlot = data->value;
        }

    } else if (data->type == EV_KEY && !m_typeB) {
        if (data->code == BTN_TOUCH && data->value == 0)
            m_contacts[m_currentSlot].state = Qt::TouchPointReleased;
    } else if (data->type == EV_SYN && data->code == SYN_MT_REPORT && m_lastEventType != EV_SYN) {

        // If there is no tracking id, one will be generated later.
        // Until that use a temporary key.
        int key = m_currentData.trackingId;
        if (key == -1)
            key = m_contacts.count();

        m_contacts.insert(key, m_currentData);
        m_currentData = Contact();

    } else if (data->type == EV_SYN && data->code == SYN_REPORT) {

        // Ensure valid IDs even when the driver does not report ABS_MT_TRACKING_ID.
        if (!m_contacts.isEmpty() && m_contacts.constBegin().value().trackingId == -1)
            assignIds();

        if (m_filtered)
            m_mutex.lock();

        // update timestamps
        m_lastTimeStamp = m_timeStamp;
        m_timeStamp = data->time.tv_sec + data->time.tv_usec / 1000000.0;
        m_lastTouchPoints = m_touchPoints;
        m_touchPoints.clear();
        Qt::TouchPointStates combinedStates;

        QMutableHashIterator<int, Contact> it(m_contacts);
        while (it.hasNext()) {
            it.next();
            Contact &contact(it.value());

            if (!contact.state)
                continue;

            int key = m_typeB ? it.key() : contact.trackingId;
            if (!m_typeB && m_lastContacts.contains(key)) {
                const Contact &prev(m_lastContacts.value(key));
                if (contact.state == Qt::TouchPointReleased) {
                    // Copy over the previous values for released points, just in case.
                    contact.x = prev.x;
                    contact.y = prev.y;
                    contact.maj = prev.maj;
                } else {
                    contact.state = (prev.x == contact.x && prev.y == contact.y)
                            ? Qt::TouchPointStationary : Qt::TouchPointMoved;
                }
            }

            // Avoid reporting a contact in released state more than once.
            if (!m_typeB && contact.state == Qt::TouchPointReleased
                    && !m_lastContacts.contains(key)) {
                it.remove();
                continue;
            }

            addTouchPoint(contact, &combinedStates);
        }

        // Now look for contacts that have disappeared since the last sync.
        it = m_lastContacts;
        while (it.hasNext()) {
            it.next();
            Contact &contact(it.value());
            int key = m_typeB ? it.key() : contact.trackingId;
            if (m_typeB) {
                if (contact.trackingId != m_contacts[key].trackingId && contact.state) {
                    contact.state = Qt::TouchPointReleased;
                    addTouchPoint(contact, &combinedStates);
                }
            } else {
                if (!m_contacts.contains(key)) {
                    contact.state = Qt::TouchPointReleased;
                    addTouchPoint(contact, &combinedStates);
                }
            }
        }

        for (int i = 0; i < m_contacts.count(); ++i) {
            qDebug() << "Contact:: x:" << m_contacts[i].x << "; y:" << m_contacts[i].y << "; pressure:" << m_contacts[i].pressure;
        }


        // Remove contacts that have just been reported as released.
        it = m_contacts;
        while (it.hasNext()) {
            it.next();
            Contact &contact(it.value());

            if (!contact.state)
                continue;

            if (contact.state == Qt::TouchPointReleased) {
                if (m_typeB)
                    contact.state = static_cast<Qt::TouchPointState>(0);
                else
                    it.remove();
            } else {
                contact.state = Qt::TouchPointStationary;
            }
        }

        m_lastContacts = m_contacts;
        if (!m_typeB && !m_singleTouch)
            m_contacts.clear();


        if (!m_touchPoints.isEmpty() && combinedStates != Qt::TouchPointStationary)
            reportPoints();

        if (m_filtered)
            m_mutex.unlock();

        qDebug() << "===================";
    }

    m_lastEventType = data->type;
}
