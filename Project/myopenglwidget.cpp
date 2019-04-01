#include "myopenglwidget.h"
#include <QPainter>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "mesh.h"
#include "submesh.h"
#include <QKeyEvent>


#pragma comment(lib, "OpenGL32.lib")

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setFocus();
    this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    myMesh = new Mesh();
    myMesh->loadModel("./Models/Patrick/Patrick.obj");

    qDebug("Number of submeshes: %i", myMesh->submeshes.count());

    //glDisable(GL_CULL_FACE);

}

void MyOpenGLWidget::resizeGL(int width, int height)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Projection/Model view setting

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*QMatrix4x4 mat;
    mat.setToIdentity();
    mat.translate(QVector3D(0.0f, 0.0f, 0.0f));
    mat.rotate(0.0f, QVector3D(0.0f, 1.0f, 0.0f));
    glLoadMatrixf(mat.data());*/

    /*
    QMatrix4x4 model;
    model.setToIdentity();
    //model.translate(QVector3D(0.0f, 0.0f, 0.0f));
    //model.rotate(0.0f, QVector3D(0.0f, 1.0f, 0.0f));

    QMatrix4x4 view;
    view.lookAt(
      QVector3D(0.0, 0.0, 0.0), // Eye
      QVector3D(0.0, 0.0, 0.0), // Focal Point
      QVector3D(0.0, 1.0, 0.0)); // Up vector

    QMatrix4x4 proj;
    // Window size is fixed at 800.0 by 600.0
    proj.perspective(45.0, 1920.0 / 1080.0, 1.0, 100.0);
    QMatrix4x4 mvp = (proj * view);
    */
    QMatrix4x4 model;
    model.setToIdentity();
    model.rotate(0.0f, QVector3D(0.0f, 1.0f, 0.0f));
    QMatrix4x4 view;
    view.setToIdentity();
    view.translate(position);
    QMatrix4x4 proj;
    proj.setToIdentity();
    proj.perspective(45.0f, 1920.0 / 1080.0, 0.1f, 100.0f);

    QMatrix4x4 mvp = (proj * view * model);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Stuff
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;
    // Program
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/shaderl_vert.vsh");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/shaderl_frag.fsh");
    program.link();
    program.bind();

    // VB0
    QVector3D vertices[] = { QVector3D(-0.5f, -0.5f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f),
                             QVector3D( 0.5f, -0.5f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f),
                             QVector3D( 0.0f, 0.5f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f) };


    int modelLoc = glGetUniformLocation(program.programId(), "mat_model");
    glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model.data());

    int projecLoc = glGetUniformLocation(program.programId(), "projection_view");
    glUniformMatrix4fv(projecLoc, 1, GL_TRUE, mvp.data());

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, 6 * sizeof(QVector3D));
    // VAO: Captures state of VBOs
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
    program. release();


    /*for(int i=0; i<myMesh->submeshes.count(); i++)
    {
        if(myMesh->submeshes[i]!=nullptr)
        {
            myMesh->submeshes[i]->update();
            qDebug("DIBUGAME");
            myMesh->submeshes[i]->draw();
            qDebug("SubMesh %i is your time", i);
        }
        else{
                qDebug("SubMesh %i is nullptr", i);
        }
    }*/

}

void MyOpenGLWidget::keyPressEvent(QKeyEvent* event)
{
    /*
    if (event->key() == Qt::Key_R) qDebug("R KEY GL");
    else qDebug("ELSE KEY GL");
    */

    if (event->key() == Qt::Key_W)
        position.setZ(position.z() + 1.0f);
    if (event->key() == Qt::Key_S)
        position.setZ(position.z() - 1.0f);
    if (event->key() == Qt::Key_A)
        position.setX(position.x() + 1.0f);
    if (event->key() == Qt::Key_D)
        position.setX(position.x() - 1.0f);

    this->repaint();
}
