#include "gcomponentrender.h"
#include"gobject.h"
#include <QPainter>
#include "gscene.h"
#include "gcomponenttransform.h"

gComponentRender::gComponentRender(gObject *parent) : gComponent (parent)
{
    compType = gComponentType::COMP_RENDER;
    shape = "Quad";
}

gComponentRender::gComponentRender(gObject *parent, gShape newShape, float newsize): gComponent (parent)
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

    brush.setColor(color);
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
    gComponentTransform* trans = static_cast<gComponentTransform*>(parent->GetComponent(gComponentType::COMP_TRANSFORM));

    int x = 0;
    int y = 0;

    if(trans!=nullptr){
        x = trans->position.x();
        y = trans->position.y();
    }

    int r = size;
    int w = r * 2;
    int h = r * 2;

    if(shape.compare("Circle")==0)
    {
        qDebug("I AM A CIRCLE");
        QRect circleRect(x,y,w,h);
        painter->drawEllipse(circleRect);
    }
    else if (shape.compare("Quad")==0) {
        qDebug("I AM A QUAD");
        QRect QuadeRect(x,y,w,h);
        painter->drawRect(QuadeRect);
    }

}
