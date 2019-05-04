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

private:
    void PassMesh(gEditorCamera *editorCamera);
    void PassMaterials();
    void PassLights();
    void PassSelectionOutline();
    void PassGrid();
    void UpdateMeshsDeferred();

public:
    //QVector<gObject*> myObjectsScene;

     GLuint colorTexture;

private:


    GLuint depthTexture;
    GLuint fbo;

    float width;
    float height;

};

#endif // GDEFERREDRENDERER_H
