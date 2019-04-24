#include "gcomponentrender.h"
#include"gobject.h"
#include <QPainter>
#include "gscene.h"
#include "gcomponenttransform.h"
#include "mesh.h"
#include "submesh.h"


gComponentRender::gComponentRender(gObject *parent) : gComponent (parent)
{
    compType = gComponentType::COMP_RENDER;
    //shape = "Patrick";
    myMesh = new Mesh();

    textureOpenGL = new QOpenGLTexture(QImage().mirrored());
    textureOpenGL->setMinificationFilter(QOpenGLTexture::Nearest);
    textureOpenGL->setMagnificationFilter(QOpenGLTexture::Linear);
    textureOpenGL->setWrapMode(QOpenGLTexture::Repeat);

    //myMesh->loadModel("Models/Patrick/Patrick.obj");
    //Update();
}

gComponentRender::gComponentRender(gObject *parent, gShape newShape, float newsize): gComponent (parent)
{
    compType = gComponentType::COMP_RENDER;
    //shape = "Patrick";
    shape = newShape;
    size = newsize;

    textureOpenGL = new QOpenGLTexture(QImage().mirrored());
    textureOpenGL->setMinificationFilter(QOpenGLTexture::Nearest);
    textureOpenGL->setMagnificationFilter(QOpenGLTexture::Linear);
    textureOpenGL->setWrapMode(QOpenGLTexture::Repeat);
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
                meshTemp->submeshes[i]->draw();
            }
        }
    }
}
