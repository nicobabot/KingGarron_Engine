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

gSaoRender::gSaoRender(int newWitdth, int newHeight)
{
    width = newWitdth;
    height = newHeight;
}

gSaoRender::~gSaoRender()
{

}

void gSaoRender::Initialize()
{

    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();

    glGenTextures(1, &ssaoTexture);
    glBindTexture(GL_TEXTURE_2D, ssaoTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    gl_functions->glGenFramebuffers(1, &fbo);
    gl_functions->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    gl_functions->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoTexture, 0);

    GLenum buffers[] = {GL_COLOR_ATTACHMENT0};
    gl_functions->glDrawBuffers(1, buffers);

    QVector<QVector3D> ssaoNoise;
    std::uniform_real_distribution<float> randomFloats(0.0, 1.0);
    std::default_random_engine generator;

    // Generation of a 4x4 texture of random vectors QVector<QVector30> ssaoNoise;
    for (unsigned int i = 0; i < 16; i++)
    {
        QVector3D noise(
        randomFloats(generator) * 2.0 - 1.0,
        randomFloats(generator) * 2.0 - 1.0,
        0.0f);
        ssaoNoise.push_back(noise);
    }

    gl_functions->glGenTextures(1, &ssaoNoiseTex);
    gl_functions->glBindTexture(GL_TEXTURE_2D, ssaoNoiseTex);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl_functions->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);

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

     programSSAO.create();
     programSSAO.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/ssao_vertexshader.vsh");
     programSSAO.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/ssao_fragmentshader.fsh");
     programSSAO.link();


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

void gSaoRender::Resize(int w, int h)
{

    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    gl_functions->glDeleteTextures(1, &ssaoTexture);
    gl_functions->glDeleteFramebuffers(1, &fbo);

    width = w;
    height = h;

    Initialize();
}

void gSaoRender::Render(gEditorCamera* editorCamera)
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    gl_functions->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glClearDepth(1.0);
    gl_functions->glClearColor(0.0f, 0.0f, 0.0f,1.0f);
    gl_functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PassSsao(editorCamera);

    QOpenGLFramebufferObject::bindDefault();
}

void gSaoRender::PassSsao(gEditorCamera* editorCamera)
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    if(programSSAO.bind())
    {
        glClearColor(0.0f, 0.0f, 0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //programSSAO.setUniformValue("typeOfRender",renderType);
        programSSAO.setUniformValue("viewport_size",QVector2D(editorCamera->widthViewport, editorCamera->heightViewport));
        programSSAO.setUniformValue("viewMatInv",editorCamera->viewMatrix.inverted());
        programSSAO.setUniformValue("projMatInv",editorCamera->projMatrix.inverted());
        programSSAO.setUniformValue("cameraPos",editorCamera->position);

        std::uniform_real_distribution<float> randomFloats(0.0, 1.0);
        std::default_random_engine generator;
        float ssaoKernel[192];

        for (unsigned int i = 0; i < 192; i+=3)
        {
         QVector3D sample(
         randomFloats(generator) * 2.0 - 1.0,
         randomFloats(generator) * 2.0 - 1.0,
         randomFloats(generator)
         );
         sample.normalize();
         sample *= randomFloats(generator);
         float scale = (float)i / 192.0;

         //LERP
         //scale = lerp(0.1f, 1.0f, scale * scale);
         scale = 0.1f + (scale * scale) * (1.0f - 0.1f);

         sample *= scale;
         ssaoKernel[i]=sample.x();
         ssaoKernel[i+1]=sample.y();
         ssaoKernel[i+2]=sample.z();
        }

        programSSAO.setUniformValueArray("samples", ssaoKernel, 192, 3);

        programSSAO.setUniformValue(programSSAO.uniformLocation("ourTexture"), 0);
        programSSAO.setUniformValue(programSSAO.uniformLocation("normalMap"), 1);
        programSSAO.setUniformValue(programSSAO.uniformLocation("depthMap"), 2);
        programSSAO.setUniformValue(programSSAO.uniformLocation("noiseMap"), 3);

        //deferred

        gl_functions->glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, deferred->GetColorTexture());

        gl_functions->glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, deferred->GetNormalTexture());

        gl_functions->glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, deferred->GetDepthTexture());

        gl_functions->glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, deferred->GetNoiseSSAOTexture());

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0,6);
    }


   // Release
   vao.release();
   vbo.release();
   programSSAO.release();
   glBindTexture(GL_TEXTURE_2D, 0);
}
