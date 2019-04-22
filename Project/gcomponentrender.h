#ifndef GCOMPONENTRENDER_H
#define GCOMPONENTRENDER_H
#include "gcomponent.h"
#include "qrect.h"
#include <QPainter>
#include <QColorDialog>

class GScene;
class Mesh;

enum gShape
{
    SPHERE,
    CUBE
};

class gComponentRender : public gComponent
{
public:
    gComponentRender(gObject *parent);
    gComponentRender(gObject *parent, gShape newShape, float newsize);
    void Update();
    void Render();

public:
    std::string shape;
    std::string material;
    float size = 50.0f;
    QColor color = QColor(1,1,1,255);

    Mesh* myMesh = nullptr;

private:

};

#endif // GCOMPONENTRENDER_H
