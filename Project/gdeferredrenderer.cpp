#include "gdeferredrenderer.h"
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>

gDeferredRenderer::gDeferredRenderer()
{

}

gDeferredRenderer::~gDeferredRenderer()
{

}

void gDeferredRenderer::Initialize()
{

    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    gl_functions->glGenFramebuffers(1, &fbo);
    gl_functions->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    gl_functions->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
    gl_functions->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    GLenum status = gl_functions->glCheckFramebufferStatus(GL_FRAMEBUFFER);
     switch(status)
     {
     case GL_FRAMEBUFFER_COMPLETE: // Everything's OK
     break;
     case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
     qDebug("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"); break;
     case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
     qDebug("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"); break;
     case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
     qDebug("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"); break;
     case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
     qDebug("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"); break;
     case GL_FRAMEBUFFER_UNSUPPORTED:
     qDebug("Framebuffer ERROR: GL_FRAMEBUFFER_UNSUPPORTED"); break;
     default:
     qDebug("Framebuffer ERROR: Unknown ERROR");
     }



}

void gDeferredRenderer::Resize(int w, int h)
{

}

void gDeferredRenderer::Render()
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    gl_functions->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glClearDepth(1.0);
    gl_functions->glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
    gl_functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PassMesh();
    //passGrid();

    QOpenGLFramebufferObject::bindDefault();


}

void gDeferredRenderer::PassMaterials()
{

}

void gDeferredRenderer::PassLights()
{

}

void gDeferredRenderer::PassSelectionOutline()
{

}

void gDeferredRenderer::PassGrid()
{

}

void gDeferredRenderer::PassMesh()
{

}
