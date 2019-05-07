#ifndef GDEFERREDRENDERER_H
#define GDEFERREDRENDERER_H

#include "grenderer.h"
#include "myopenglwidget.h"

class gEditorCamera;

class gDeferredRenderer : gRenderer
{
public:
    gDeferredRenderer(int newWitdth, int newHeight);
    ~gDeferredRenderer();
    void Initialize();
    void Resize(int w, int h);
    void Render(gEditorCamera *editorCamera);
    GLuint GetColorTexture(){ return colorTexture;};
    GLuint GetDepthTexture(){ return colorTexture;};
    GLuint GetNormalTexture(){ return normalTexture;};

private:
    void PassMesh(gEditorCamera *editorCamera);
    void PassMaterials();
    void PassLights();
    void PassSelectionOutline();
    void PassGrid();
    void UpdateMeshsDeferred();

private:
    GLuint colorTexture;
    GLuint depthTexture;
    GLuint normalTexture;
    GLuint fbo;

    float width;
    float height;

};

#endif // GDEFERREDRENDERER_H
