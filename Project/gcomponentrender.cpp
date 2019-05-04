#include "gcomponentrender.h"
#include"gobject.h"
#include <QPainter>
#include "gscene.h"
#include "gcomponenttransform.h"
#include "mesh.h"
#include "submesh.h"
#include "myopenglwidget.h"
#include <qopengltexture.h>

gComponentRender::gComponentRender(gObject *parent) : gComponent (parent)
{
    compType = gComponentType::COMP_RENDER;
    //shape = "Patrick";
    myMesh = new Mesh();
    myProgram.create();
    myProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/shaderl_vert.vsh");
    myProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/shaderl_frag.fsh");
    myProgram.link();

    InitializeTextures();

    /*textureOpenGL = new QOpenGLTexture(QImage().mirrored());
    textureOpenGL->setMinificationFilter(QOpenGLTexture::Nearest);
    textureOpenGL->setMagnificationFilter(QOpenGLTexture::Linear);
    textureOpenGL->setWrapMode(QOpenGLTexture::Repeat);*/

    //myMesh->loadModel("Models/Patrick/Patrick.obj");
    //Update();
}

gComponentRender::gComponentRender(gObject *parent, gShape newShape, float newsize): gComponent (parent)
{
    compType = gComponentType::COMP_RENDER;
    //shape = "Patrick";
    shape = newShape;
    size = newsize;
    myProgram.create();
    myProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/shaderl_vert.vsh");
    myProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/shaderl_frag.fsh");
    myProgram.link();

    InitializeTextures();

    /*textureOpenGL = new QOpenGLTexture(QImage().mirrored());
    textureOpenGL->setMinificationFilter(QOpenGLTexture::Nearest);
    textureOpenGL->setMagnificationFilter(QOpenGLTexture::Linear);
    textureOpenGL->setWrapMode(QOpenGLTexture::Repeat);*/
}

void gComponentRender::InitializeTextures()
{
    Mesh* meshTemp = myMesh;

    if(meshTemp!=nullptr)
    {
      for(int i=0; i<meshTemp->submeshes.count(); i++)
      {
          if(meshTemp->submeshes[i]!=nullptr)
          {
          meshTemp->submeshes[i]->textureOpenGL = new QOpenGLTexture(QImage().mirrored());
          }
      }
  }
}

void gComponentRender::Update()
{
    Mesh* meshTemp = myMesh;

    if(meshTemp!=nullptr){

      for(int i=0; i<meshTemp->submeshes.count(); i++)
      {
          if(meshTemp->submeshes[i]!=nullptr)
          {
          meshTemp->submeshes[i]->update();
          }
      }
  }
}

void gComponentRender::Render()
{
  Mesh* meshTemp = myMesh;

  if(meshTemp!=nullptr)
  {
        for(int i=0; i<meshTemp->submeshes.count(); i++)
        {
            if(meshTemp->submeshes[i]!=nullptr)
            {
                if(meshTemp->submeshes[i]->textureOpenGL!=nullptr)
                {
                    glBindTexture(GL_TEXTURE_2D, meshTemp->submeshes[i]->textureOpenGL->textureId());
                }

                meshTemp->submeshes[i]->draw();

                if(meshTemp->submeshes[i]->textureOpenGL!=nullptr)
                {
                    glBindTexture(GL_TEXTURE_2D, 0);
                }

            }
        }
    }
}
