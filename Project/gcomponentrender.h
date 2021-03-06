#ifndef GCOMPONENTRENDER_H
#define GCOMPONENTRENDER_H
#include "gcomponent.h"
#include "qrect.h"
#include <QPainter>
#include <QColorDialog>
#include <qopengltexture.h>
#include <qimage.h>
#include <QOpenGLShaderProgram>

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
    void InitializeTextures();
    void ReloadMyShader();

public:
    std::string shape;
    std::string matAlbedo;
    std::string matNormal;
    float size = 50.0f;
    QColor color = QColor(1,1,1,255);

    int textureSample = 0;
    Mesh* myMesh = nullptr;
    QOpenGLShaderProgram myProgram;


private:

};

#endif // GCOMPONENTRENDER_H
