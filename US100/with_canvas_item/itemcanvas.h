#ifndef ITEMCANVAS_H
#define ITEMCANVAS_H
#include <QQuickPaintedItem>
#include <QPainter>

class ItemCanvas : public QQuickPaintedItem
{
public:
    explicit ItemCanvas(QQuickItem *parent = 0);

    void paint(QPainter *painter);
};

#endif // ITEMCANVAS_H
