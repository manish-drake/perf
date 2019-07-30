#ifndef TOUCHY_H
#define TOUCHY_H

#include <QObject>
#include <linux/input.h>
#include <QTouchDevice>
#include <QTouchEvent>
#include <qwindowsysteminterface.h>

class QEvdevTouchScreenData;
class touchy : public QObject
{
    Q_OBJECT
    QEvdevTouchScreenData *d;
    QTouchDevice *m_device;
    int m_fd;

#define QT_NO_MTDEV
#define LONG_BITS (sizeof(long) << 3)
#define NUM_LONGS(bits) (((bits) + LONG_BITS - 1) / LONG_BITS)

public:
    explicit touchy(QObject *parent = nullptr);
    QTouchDevice *touchDevice() const
    {
        return m_device;
    }
    void registerDevice();
    static inline bool testBit(long bit, const long *array)
    {
        return (array[bit / LONG_BITS] >> bit % LONG_BITS) & 1;
    }
    ~touchy();
signals:
    void touchPointsUpdated();

public slots:
    void run(int fd);
};

#endif // TOUCHY_H
