#include "myopenglwidget.h"
#include "gprimitive.h"
#include <QPainter>
#pragma comment(lib, "OpenGL32.lib")


MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

void MyOpenGLWidget::initializeGL()
{

}

void MyOpenGLWidget::resizeGL(int width, int height)
{

}

void MyOpenGLWidget::paintGL()
{

    glClearColor(1.0f, 0.0f, 0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
