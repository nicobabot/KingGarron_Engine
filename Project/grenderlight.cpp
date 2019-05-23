#include "grenderlight.h"
#include "gsaorender.h"
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include "gcomponenttransform.h"
#include "gcomponentrender.h"
#include "gobject.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "myopenglwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "geditorcamera.h"
#include "qopenglextrafunctions.h"
#include <random>
#include "gdeferredrenderer.h"
#include <QVector2D>

gRenderLight::gRenderLight(int newWitdth, int newHeight)
{
    width = newWitdth;
    height = newHeight;
}

gRenderLight::~gRenderLight()
{

}

void gRenderLight::Initialize()
{
    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();

     static bool oneTime = true;

     if(oneTime)
     {
        oneTime = false;
        programLight.create();
        programLight.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/shaderl_vert_copy.vsh");
        programLight.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/shaderl_frag_copy.fsh");
        programLight.link();
     }


     float verticesQuad[] = {     /*Position*/-1.0f, -1.0f, 0.0f, /*Color*/ 1.0f, 1.0f, 1.0f,  /*TextureCoord*/ 0.0f, 0.0f,
                                               1.0f, 1.0f, 0.0f,            1.0f, 1.0f, 1.0f,                   1.0f, 1.0f,
                                               -1.0f, 1.0f, 0.0f,           1.0f, 1.0f, 1.0f,                   0.0f, 1.0f,
                                               -1.0f, -1.0f, 0.0f,          1.0f, 1.0f, 1.0f,                   0.0f, 0.0f,
                                                1.0f, -1.0f, 0.0f,          1.0f, 1.0f, 1.0f,                   1.0f, 0.0f,
                                                1.0f, 1.0f, 0.0f,           1.0f, 1.0f, 1.0f,                   1.0f, 1.0f };

  if(!vbo.isCreated())
         vbo.create();
     vbo.bind();
     vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
     vbo.allocate(verticesQuad, 49 * sizeof(float));
     // VAO: Captures state of VBOs
     if(!vao.isCreated())
         vao.create();
     vao.bind();
     const GLint compCount = 3;
     const int strideBytes = 8 * sizeof(float);
     const int offsetBytesO = 0;
     const int offsetBytesl = sizeof(float)*3;
     const int offsetBytes2 = sizeof(float)*6;
     gl_functions->glEnableVertexAttribArray(0);
     gl_functions->glEnableVertexAttribArray(1);
     gl_functions->glEnableVertexAttribArray(2);
     gl_functions->glVertexAttribPointer(0, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytesO));
     gl_functions->glVertexAttribPointer(1, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytesl));
     gl_functions->glVertexAttribPointer(2, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes2));

}

void gRenderLight::Resize(int w, int h)
{

    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    width = w;
    height = h;

    Initialize();
}

void gRenderLight::Render(gEditorCamera* editorCamera)
{    
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();
    gl_functions->glEnable(GL_BLEND);
    gl_functions->glBlendFunc(GL_ONE, GL_ONE);

    gl_functions->glClearDepthf(1.0);
    gl_functions->glClearColor(0.0f, 0.0f, 0.0f,0.0f);
    gl_functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl_functions->glDisable(GL_DEPTH_TEST);

    PassLightAmbient(editorCamera);

    if(renderType == RenderType::LIGHT_RENDER)
    {
    PassLightDir(editorCamera);
    }

    gl_functions->glEnable(GL_DEPTH_TEST);
    gl_functions->glDisable(GL_BLEND);
    QOpenGLFramebufferObject::bindDefault();
}

void gRenderLight::ReloadShaders()
{
    if(programLight.isLinked())
    {
        programLight.removeAllShaders();

        programLight.create();
        programLight.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/shaderl_vert_copy.vsh");
        programLight.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/shaderl_frag_copy.fsh");
        programLight.link();
    }
}

void gRenderLight::PassLightAmbient(gEditorCamera *editorCamera)
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    if(programLight.bind())
    {
        programLight.setUniformValue("typeOfRender", renderType);
        programLight.setUniformValue("typeRenderLight",0);
        programLight.setUniformValue("viewport_size",QVector2D(editorCamera->widthViewport, editorCamera->heightViewport));
        programLight.setUniformValue("viewMatInv",editorCamera->viewMatrix.inverted());
        programLight.setUniformValue("projMatInv",editorCamera->projMatrix.inverted());
        programLight.setUniformValue("cameraPos",editorCamera->position);

        programLight.setUniformValue(programLight.uniformLocation("ourTexture"), 0);
        programLight.setUniformValue(programLight.uniformLocation("normalMap"), 1);
        programLight.setUniformValue(programLight.uniformLocation("depthMap"), 2);
        programLight.setUniformValue(programLight.uniformLocation("saoMap"), 3);

        gl_functions->glActiveTexture(GL_TEXTURE0);
        gl_functions->glBindTexture(GL_TEXTURE_2D, deferred->GetColorTexture());

        gl_functions->glActiveTexture(GL_TEXTURE1);
        gl_functions->glBindTexture(GL_TEXTURE_2D, deferred->GetNormalTexture());

        gl_functions->glActiveTexture(GL_TEXTURE2);
        gl_functions->glBindTexture(GL_TEXTURE_2D, deferred->GetDepthTexture());

        gl_functions->glActiveTexture(GL_TEXTURE3);
        gl_functions->glBindTexture(GL_TEXTURE_2D, saoRender->GetSSAOTexture());

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0,6);

       programLight.release();
    }

    // Release
    //vao.release();
    //glBindTexture(GL_TEXTURE_2D, 0);
}

void gRenderLight::PassLightDir(gEditorCamera *editorCamera)
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    if(programLight.bind())
    {
        //qDebug("Holaaaaa");

        programLight.setUniformValue("typeRenderLight",1);
        programLight.setUniformValue("viewport_size",QVector2D(editorCamera->widthViewport, editorCamera->heightViewport));
        programLight.setUniformValue("viewMatInv",editorCamera->viewMatrix.inverted());
        programLight.setUniformValue("projMatInv",editorCamera->projMatrix.inverted());
        programLight.setUniformValue("cameraPos",editorCamera->position);

        programLight.setUniformValue(programLight.uniformLocation("ourTexture"), 0);
        programLight.setUniformValue(programLight.uniformLocation("normalMap"), 1);
        programLight.setUniformValue(programLight.uniformLocation("depthMap"), 2);
        programLight.setUniformValue(programLight.uniformLocation("saoMap"), 3);

        gl_functions->glActiveTexture(GL_TEXTURE0);
        gl_functions->glBindTexture(GL_TEXTURE_2D, deferred->GetColorTexture());

        gl_functions->glActiveTexture(GL_TEXTURE1);
        gl_functions->glBindTexture(GL_TEXTURE_2D, deferred->GetNormalTexture());

        gl_functions->glActiveTexture(GL_TEXTURE2);
        gl_functions->glBindTexture(GL_TEXTURE_2D, deferred->GetDepthTexture());

        gl_functions->glActiveTexture(GL_TEXTURE3);
        gl_functions->glBindTexture(GL_TEXTURE_2D, saoRender->GetSSAOTexture());

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0,6);

        programLight.release();
    }

    // Release
    //vao.release();
    glBindTexture(GL_TEXTURE_2D, 0);
}
