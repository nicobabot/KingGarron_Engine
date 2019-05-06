#include "gdeferredrenderer.h"
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

gDeferredRenderer::gDeferredRenderer(int newWitdth, int newHeight)
{
    width = newWitdth;
    height = newHeight;
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

void gDeferredRenderer::Render(gEditorCamera* editorCamera)
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    gl_functions->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glClearDepth(1.0);
    gl_functions->glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    gl_functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    PassMesh(editorCamera);
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

void gDeferredRenderer::PassMesh(gEditorCamera *editorCamera)
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();


    if(mainWindow->openGLWidget->needUpdate)
    {
        qDebug("UPDATE MESH");
        UpdateMeshsDeferred();
         mainWindow->openGLWidget->needUpdate = false;
    }

    for(gObject* myObject : mainWindow->openGLWidget->myObjectsScene)
    {
        if(myObject==nullptr)
            continue;

        gComponentTransform *trans = (gComponentTransform*)myObject->GetComponent(gComponentType::COMP_TRANSFORM);

        QVector3D position = trans->position;

        float rotx, roty, rotz;
        trans->rotation.getEulerAngles(&rotx, &roty, &rotz);

        QVector3D scale = trans->scale;
        QMatrix4x4 model;
        model.translate(QVector3D(position.x(), position.y(), position.z()));
        model.rotate(trans->rotation);
        model.scale(QVector3D(scale.x(), scale.y(), scale.z()));

        gComponentRender *render = (gComponentRender*)myObject->GetComponent(gComponentType::COMP_RENDER);

        render->myProgram.bind();
        if(render->myProgram.isLinked())
        {
        int projecLoc = gl_functions->glGetUniformLocation(render->myProgram.programId(), "projection");
        gl_functions->glUniformMatrix4fv(projecLoc, 1, GL_TRUE, editorCamera->projMatrix.transposed().data());

        //qDebug("Proj %i", projecLoc);

        int viewLoc = gl_functions->glGetUniformLocation(render->myProgram.programId(), "view");
        gl_functions->glUniformMatrix4fv(viewLoc, 1, GL_TRUE, editorCamera->viewMatrix.transposed().data());

        //qDebug("View %i", viewLoc);

        int modelLoc = gl_functions->glGetUniformLocation(render->myProgram.programId(), "model");
        gl_functions->glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model.transposed().data());

        //qDebug("Model %i", modelLoc);

        }

        gl_functions->glActiveTexture(GL_TEXTURE0);

        /*if(render->textureOpenGL!=nullptr)
        {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, render->textureOpenGL->textureId());
        }*/
        render->Render();
    }
}

void gDeferredRenderer::UpdateMeshsDeferred()
{
    for(gObject* myObject :  mainWindow->openGLWidget->myObjectsScene)
    {
        if(myObject==nullptr)
            continue;

           gComponentRender *render = (gComponentRender*)myObject->GetComponent(gComponentType::COMP_RENDER);

         if(render==nullptr)
             continue;

         render->Update();

    }
}
