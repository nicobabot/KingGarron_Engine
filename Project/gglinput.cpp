#include "gglinput.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QEvent>
#include "myopenglwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

gGLInput::gGLInput()
{

}

void gGLInput::Update()
{

}

void gGLInput::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;
    if (MyOpenGLWidget* OGLWidget = mainWindow->openGLWidget)
    {
        if (event->key() == Qt::Key_W)
            OGLWidget->position.setZ(OGLWidget->position.z() + 1.0f);
        if (event->key() == Qt::Key_S)
            OGLWidget->position.setZ(OGLWidget->position.z() - 1.0f);
        if (event->key() == Qt::Key_A)
            OGLWidget->position.setX(OGLWidget->position.x() + 1.0f);
        if (event->key() == Qt::Key_D)
            OGLWidget->position.setX(OGLWidget->position.x() - 1.0f);
    }
}

void gGLInput::keyReleaseEvent(QKeyEvent* event)
{

}

void gGLInput::mousePressEvent(QMouseEvent* event)
{

}

void gGLInput::mouseMoveEvent(QMouseEvent* event)
{

}

void gGLInput::mouseReleaseEvent(QMouseEvent* event)
{

}

void gGLInput::enterEvent(QEvent* event)
{

}

void gGLInput::leaveEvent(QEvent* event)
{

}
