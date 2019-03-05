#ifndef GCOMPONENTRENDER_H
#define GCOMPONENTRENDER_H
#include "gcomponent.h"
#include "qrect.h"

enum gShape{
    SPHERE,
    CUBE
};

class gComponentRender : public gComponent
{
public:
    gComponentRender();
    gComponentRender(gShape newShape, float newsize);
    void gPaintObject(gObject* obj, QRect rect);
public:
    gShape shape;
    float size;
};

#endif // GCOMPONENTRENDER_H
