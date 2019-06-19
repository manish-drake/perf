#include "itemcanvas.h"

ItemCanvas::ItemCanvas(QQuickItem *parent):
    QQuickPaintedItem(parent)
{
//    update();
}

void ItemCanvas::paint(QPainter *painter)
{
    painter->drawText(90,70,480,25, 0,"Label1");
    painter->drawText(90,120,480,25, 0,"Label2");
    painter->drawText(90,170,480,25, 0,"Label3");
    painter->drawText(90,220,480,25, 0,"Label4");
    painter->drawText(300,70,480,25, 0,"Label5");
    painter->drawText(300,120,480,25, 0,"Label6");
    painter->drawText(300,170,480,25, 0,"Label7");
    painter->drawText(300,220,480,25, 0,"Label8");
    painter->drawText(90,450,480,25, 0,"Label9");
    painter->drawText(90,500,480,25, 0,"Label10");
    painter->drawText(90,550,480,25, 0,"Label11");
    painter->drawText(90,600,480,25, 0,"Label12");
    painter->drawText(300,450,480,25, 0,"Label13");
    painter->drawText(300,500,480,25, 0,"Label14");
    painter->drawText(300,550,480,25, 0,"Label15");
    painter->drawText(300,600,480,25, 0,"Label16");

}
