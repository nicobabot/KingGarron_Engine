#ifndef GSAORENDER_H
#define GSAORENDER_H

#include "grenderer.h"
#include "myopenglwidget.h"

class gEditorCamera;

class gSaoRender : public gRenderer
{
public:
    gSaoRender(int newWitdth, int newHeight);
    ~gSaoRender();
    void Initialize();
    void Resize(int w, int h);
    void Render(gEditorCamera *editorCamera);
    GLuint GetNoiseSSAOTexture(){ return ssaoNoiseTex;}
    void SetDeferredRender(gDeferredRenderer* newDeferred){deferred = newDeferred;}

private:
    void PassSsao(gEditorCamera* editorCamera);

private:
    GLuint ssaoTexture;
    GLuint ssaoNoiseTex;
    GLuint fbo;

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;

    gDeferredRenderer* deferred = nullptr;

    QOpenGLShaderProgram programSSAO;

    float width;
    float height;

};
#endif // GSAORENDER_H
