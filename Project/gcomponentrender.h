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
    void gPaintObject(GScene* obj);
private:
    void RenderShapeType(QPainter *painter);
public:
    std::string shape;
    float size = 50.0f;
    QColor color = QColor(1,1,1,255);

    Mesh* myMesh;

private:
    QColor blueColor = QColor::fromRgb(127,190,220);
    QColor whiteColor = QColor::fromRgb(255,255,255);
    QColor blackColor = QColor::fromRgb(0,0,0);
    QPainter painter;
    QBrush brush;
    QPen pen;
};

#endif // GCOMPONENTRENDER_H
