#include "myopenglwidget.h"
#include <QPainter>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "mesh.h"
#include "submesh.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QEvent>
#include "gglinput.h"
#include "geditorcamera.h"
#include <gobject.h>
#include <gcomponentrender.h>

#pragma comment(lib, "OpenGL32.lib")

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setFocus();
    this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    inputClass = new gGLInput();
    editorCamera = new gEditorCamera();

    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(Update()));
    if (format().swapInterval() == -1)
        timer.setInterval(17);
    else
        timer.setInterval(0);
    timer.start();
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    delete inputClass;
    delete editorCamera;
    makeCurrent();
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    /*Mesh* objMesh = new Mesh();
    objMesh->loadModel("D:/CITM/4rto/Prog Grafica/KingGarron/KingGarron_Engine/Project/Models/Patrick/Patrick.obj");

    myMeshScene.push_back(objMesh);

    //UpdateMeshs();

    needUpdate = true;*/

    // Program
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/shaderl_vert.vsh");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/shaderl_frag.fsh");
    program.link();

    // VB0

    //glDisable(GL_CULL_FACE);

}

void MyOpenGLWidget::resizeGL(int width, int height)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    QVector3D vertices[] = { QVector3D(-0.5f, -0.5f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f),
                             QVector3D( 0.5f, -0.5f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f),
                             QVector3D( 0.0f, 0.5f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f) };

    QMatrix4x4 model;
    model.setToIdentity();
    model.translate(QVector3D(1.0f, 0.0f, 0.0f));
    model.rotate(0.0f, QVector3D(0.0f, 1.0f, 0.0f));
    model.scale(QVector3D(1.0f, 1.0f, 1.0f));
    QMatrix4x4 view;
    view.setToIdentity();
    model.translate(editorCamera->position);
    model.rotate(0.0f, QVector3D(0.0f, 1.0f, 0.0f));
    model.scale(QVector3D(1.0f, 1.0f, 1.0f));
    //view.setColumn(3, QVector4D(position,1));
    //model.rotate(0.0f, QVector3D(0.0f, 1.0f, 0.0f));
    QMatrix4x4 proj;
    proj.setToIdentity();
    proj.perspective(90.0f, static_cast<float>(width()) / static_cast<float>(height()), 0.1f, 100.0f);

    QMatrix4x4 mvp = (proj * view * model);
    mvp = mvp.transposed();
    program.bind();

    int modelLoc = glGetUniformLocation(program.programId(), "mat_model");
    glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model.data());

    int projecLoc = glGetUniformLocation(program.programId(), "projection_view");
    glUniformMatrix4fv(projecLoc, 1, GL_TRUE, mvp.data());
    if(!vbo.isCreated())
        vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, 6 * sizeof(QVector3D));
    // VAO: Captures state of VBOs
    if(!vao.isCreated())
        vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 2 * sizeof(QVector3D);
    const int offsetBytesO = 0;
    const int offsetBytesl = sizeof(QVector3D);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytesO));
    glVertexAttribPointer(1, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytesl));

    if(program.bind())
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0,3);
    }

    // Release
    vao.release();
    vbo.release();

    if(needUpdate)
    {
        qDebug("UPDATE MESH");
        UpdateMeshs();
        needUpdate = false;
    }

    for(gObject* myObject : myObjectsScene)
    {
        if(myObject==nullptr)
            continue;

           gComponentRender *render = (gComponentRender*)myObject->GetComponent(gComponentType::COMP_RENDER);

         if(render==nullptr)
             continue;

          Mesh* meshTemp = render->myMesh;

          for(int i=0; i<meshTemp->submeshes.count(); i++)
          {
            if(meshTemp->submeshes[i]!=nullptr)
            {
                meshTemp->submeshes[i]->draw();
            }
          }
    }
    program. release();
}


void MyOpenGLWidget::UpdateMeshs()
{
    for(gObject* myObject : myObjectsScene)
    {
        if(myObject==nullptr)
            continue;

           gComponentRender *render = (gComponentRender*)myObject->GetComponent(gComponentType::COMP_RENDER);

         if(render==nullptr)
             continue;

          Mesh* meshTemp = render->myMesh;

          for(int i=0; i<meshTemp->submeshes.count(); i++)
          {
            if(meshTemp->submeshes[i]!=nullptr)
            {
                meshTemp->submeshes[i]->update();
            }
          }
    }
}

void MyOpenGLWidget::Update()
{
    inputClass->Update();
    editorCamera->Update();
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent* event)
{
    inputClass->keyPressEvent(event);
    this->repaint();
}

void MyOpenGLWidget::keyReleaseEvent(QKeyEvent* event)
{
    inputClass->keyReleaseEvent(event);
    this->repaint();
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    inputClass->mousePressEvent(event);
    this->repaint();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    inputClass->mouseMoveEvent(event);
    this->repaint();
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    inputClass->mouseReleaseEvent(event);
    this->repaint();
}

void MyOpenGLWidget::enterEvent(QEvent* event)
{
    inputClass->enterEvent(event);
    this->repaint();
}

void MyOpenGLWidget::leaveEvent(QEvent* event)
{
    inputClass->leaveEvent(event);
    this->repaint();
}
