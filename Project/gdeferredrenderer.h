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
    GLuint GetDepthTexture(){ return depthTexture;};
    GLuint GetNormalTexture(){ return normalTexture;};
    GLuint GetNoiseSSAOTexture(){ return ssaoNoiseTex;};

private:
    void PassMesh(gEditorCamera *editorCamera);
    void UpdateMeshsDeferred();

private:
    GLuint colorTexture;
    GLuint depthTexture;
    GLuint normalTexture;
    GLuint ssaoNoiseTex;
    GLuint fbo;

    float width;
    float height;

};

#endif // GDEFERREDRENDERER_H
