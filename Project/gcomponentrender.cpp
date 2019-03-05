#include "gcomponentrender.h"
#include"gobject.h"
#include <QPainter>

gComponentRender::gComponentRender()
{
    compType = gComponentType::COMP_RENDER;
}

gComponentRender::gComponentRender(gShape newShape, float newsize)
{
    compType = gComponentType::COMP_RENDER;
    shape = newShape;
    size = newsize;
}

void gComponentRender::gPaintObject(gObject* obj, QRect rect)
{
    QColor blueColor = QColor::fromRgb(127,190,220);
    QColor whiteColor = QColor::fromRgb(255,255,255);
    QColor blackColor = QColor::fromRgb(0,0,0);

    QPainter painter;
    QBrush brush;
    QPen pen;

    painter.begin(obj);
    brush.setColor(blueColor);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawRect(rect);

    brush.setColor(whiteColor);
    pen.setWidth(4);
    pen.setColor(blackColor);
    pen.setStyle(Qt::PenStyle::DashLine);
    painter.setBrush(brush);
    painter.setPen(pen);

    int r = 64;
    int w = r*2;
    int h = r*2;
    int x = rect.width() / 2 - r;
    int y = rect.height() / 2 - r;
    QRect circleRect(x,y,w,h);
    painter.drawEllipse(circleRect);

    painter.end();
}
