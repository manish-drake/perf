#ifndef TOUCHY_H
#define TOUCHY_H

#include <QObject>
#include <linux/input.h>
#include <QTouchDevice>
#include <QTouchEvent>

class QEvdevTouchScreenData;
class touchy : public QObject
{
    Q_OBJECT
    QEvdevTouchScreenData *d;
    QTouchDevice *m_device;
    int m_fd;
public:
    explicit touchy(QObject *parent = nullptr);
    QTouchDevice *touchDevice() const
    {
        return m_device;
    }
    ~touchy();
signals:
    void touchPointsUpdated();

public slots:
    void run(int fd);
};

#endif // TOUCHY_H
