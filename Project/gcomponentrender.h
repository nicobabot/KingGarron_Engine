#ifndef GCOMPONENTRENDER_H
#define GCOMPONENTRENDER_H
#include "gcomponent.h"
#include "qrect.h"
#include <QPainter>

class GScene;

enum gShape{
    SPHERE,
    CUBE
};

class gComponentRender : public gComponent
{
public:
    gComponentRender();
    gComponentRender(gShape newShape, float newsize);
    void gPaintObject(GScene* obj, QRect rect);
private:
    void RenderShapeType(QPainter painter);

public:
    gShape shape;
    float size;
};

#endif // GCOMPONENTRENDER_H
