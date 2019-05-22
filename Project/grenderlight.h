#ifndef GRENDERLIGHT_H
#define GRENDERLIGHT_H

#include "grenderer.h"
#include "myopenglwidget.h"

class gEditorCamera;

class gRenderLight : public gRenderer
{
public:
    gRenderLight(int newWitdth, int newHeight);
    ~gRenderLight();
    void Initialize();
    void Resize(int w, int h);
    void Render(gEditorCamera *editorCamera);
    void SetSSAORender(gSaoRender* newSsao){saoRender = newSsao;}
    void SetDeferredRender(gDeferredRenderer* newDeferred){deferred = newDeferred;}

private:
    void PassLightAmbient(gEditorCamera* editorCamera);
    void PassLightDir(gEditorCamera* editorCamera);

private:
    //GLuint lightTexture;
    //GLuint fbo;

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;

    gDeferredRenderer* deferred = nullptr;
    gSaoRender *saoRender = nullptr;

    QOpenGLShaderProgram programLight;

    float width;
    float height;

};

#endif // GRENDERLIGHT_H
