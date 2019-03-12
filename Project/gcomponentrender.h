#ifndef GCOMPONENTRENDER_H
#define GCOMPONENTRENDER_H
#include "gcomponent.h"
#include "qrect.h"
#include <QPainter>
#include <QColorDialog>

class GScene;

enum gShape{
    SPHERE,
    CUBE
};

class gComponentRender : public gComponent
{
public:
    gComponentRender(gObject *parent);
    gComponentRender(gObject *parent, gShape newShape, float newsize);
    void gPaintObject(GScene* obj, QRect rect);
private:
    void RenderShapeType(QPainter *painter, QRect rect);

public:
    //gShape shape;
    std::string shape;
    float size = 50.0f;
    QColor color = QColor(1,1,1,255);
};

#endif // GCOMPONENTRENDER_H
