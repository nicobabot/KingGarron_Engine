#ifndef GDEFERREDRENDERER_H
#define GDEFERREDRENDERER_H

#include "grenderer.h"
#include "myopenglwidget.h"

class gDeferredRenderer : gRenderer
{
public:
    gDeferredRenderer();
    ~gDeferredRenderer();
    void Initialize();
    void Resize(int w, int h);
    void Render();
private:
    void PassMesh();
    void PassMaterials();
    void PassLights();
    void PassSelectionOutline();
    void PassGrid();

private:

    GLuint colorTexture;
    GLuint depthTexture;
    GLuint fbo;

    float width;
    float height;

};

#endif // GDEFERREDRENDERER_H
