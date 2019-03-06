#include "gcomponentrender.h"
#include"gobject.h"
#include <QPainter>
#include "gscene.h"

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

void gComponentRender::gPaintObject(GScene* obj, QRect rect)
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

    brush.setColor(whiteColor);
    pen.setWidth(4);
    pen.setColor(blackColor);
    pen.setStyle(Qt::PenStyle::DashLine);
    painter.setBrush(brush);
    painter.setPen(pen);


    painter.end();
}

void gComponentRender::RenderShapeType(QPainter painter)
{
    int r = 0;
    int w = 0;
    int h = 0;
    int x = 0;
    int y = 0;

    switch(shape)
    {
    case gShape::SPHERE:
    {
        r = 64;
        w = r*2;
        h = r*2;
        x = size / 2 - r;
        y = size / 2 - r;
        QRect circleRect(x,y,w,h);
        painter.drawEllipse(circleRect);
    }
        break;

     case gShape::CUBE:
    {
        w = r*2;
        h = r*2;
        x = size / 2 ;
        y = size / 2;
        QRect QuadeRect(x,y,w,h);
        painter.drawRect(QuadeRect);
    }
        break;

     default:
    {}
        break;
    }
}
