#include "myopenglwidget.h"
#include <QPainter>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#pragma comment(lib, "OpenGL32.lib")

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

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

    //glDisable(GL_CULL_FACE);

}

void MyOpenGLWidget::resizeGL(int width, int height)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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


}
