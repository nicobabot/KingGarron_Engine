#ifndef GRENDERLIGHT_H
#define GRENDERLIGHT_H

#include "grenderer.h"
#include "myopenglwidget.h"

class gEditorCamera;

enum RenderType{
    ALBEDO_RENDER,
    NORMAL_RENDER,
    DEPTH_RENDER,
    SSAO_RENDER,
    LIGHT_RENDER
};

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
    void ReloadShaders();
private:
    void PassLightAmbient(gEditorCamera* editorCamera);
    void PassLightDir(gEditorCamera* editorCamera);

public:
     RenderType renderType = RenderType::LIGHT_RENDER;

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
