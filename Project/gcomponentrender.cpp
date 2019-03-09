#include "gcomponentrender.h"
#include"gobject.h"
#include <QPainter>
#include "gscene.h"

gComponentRender::gComponentRender()
{
    compType = gComponentType::COMP_RENDER;
    shape = "Quad";
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

    //painter.drawRect(rect);

    brush.setColor(whiteColor);
    pen.setWidth(4);
    pen.setColor(blackColor);
    pen.setStyle(Qt::PenStyle::DashLine);
    painter.setBrush(brush);
    painter.setPen(pen);


    RenderShapeType(&painter, rect);
    painter.end();





}

void gComponentRender::RenderShapeType(QPainter *painter, QRect rect)
{
    int r = 0;
    int w = 0;
    int h = 0;
    int x = 0;
    int y = 0;

    if(shape.compare("Circle")==0)
    {
        qDebug("I AM A CIRCLE");
        r = 64;
        w = r * 2;
        h = r * 2;
        x = rect.width() / 2 - r;
        y = rect.height() / 2 - r;
        QRect circleRect(x,y,w,h);
        painter->drawEllipse(circleRect);
    }
    else if (shape.compare("Quad")==0) {
        qDebug("I AM A QUAD");
        r = 64;
        w = r * 2;
        h = r * 2;
        x = rect.width() / 2 - r;
        y = rect.height() / 2 - r;
        QRect QuadeRect(x,y,w,h);
        painter->drawRect(QuadeRect);
    }

}
