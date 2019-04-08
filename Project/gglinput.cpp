#include "gglinput.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QEvent>
#include "myopenglwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "geditorcamera.h"

gGLInput::gGLInput()
{
    memset(keyboard, KEY_STATE::KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
    memset(keyboardOld, KEY_STATE::KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
    memset(mouse_buttons, KEY_STATE::KEY_IDLE, sizeof(KEY_STATE) * MAX_BUTTONS);
}

void gGLInput::Update()
{
    for(int id : keyboard)
        if (keyboardOld[id] == keyboard[id])
            if (keyboardOld[id] == KEY_STATE::KEY_DOWN && keyboard[id] == KEY_STATE::KEY_DOWN) keyboard[id] = KEY_STATE::KEY_REPEAT;
    memcpy(keyboardOld, keyboard, sizeof(KEY_STATE) * MAX_KEYS);
    qDebug("R: %i", keyboard[Qt::Key_R]);
}

KEY_STATE gGLInput::GetKey(int id) const
{
    return keyboard[id];
}

KEY_STATE gGLInput::GetMouseButton(int id) const
{
    return mouse_buttons[id];
}

int gGLInput::GetMouseX() const
{
    return mouse_x;
}

int gGLInput::GetMouseY() const
{
    return mouse_y;
}

int gGLInput::GetMouseZ() const
{
    return mouse_z;
}

int gGLInput::GetMouseXMotion() const
{
    return mouse_x_motion;
}

int gGLInput::GetMouseYMotion() const
{
    return mouse_y_motion;
}

void gGLInput::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;
    keyboard[event->key()] = KEY_STATE::KEY_DOWN;
    if (MyOpenGLWidget* OGLWidget = mainWindow->openGLWidget)
    {
        if (event->key() == Qt::Key_W)
            OGLWidget->editorCamera->position.setZ(OGLWidget->editorCamera->position.z() + 1.0f);
        if (event->key() == Qt::Key_S)
            OGLWidget->editorCamera->position.setZ(OGLWidget->editorCamera->position.z() - 1.0f);
        if (event->key() == Qt::Key_A)
            OGLWidget->editorCamera->position.setX(OGLWidget->editorCamera->position.x() + 1.0f);
        if (event->key() == Qt::Key_D)
            OGLWidget->editorCamera->position.setX(OGLWidget->editorCamera->position.x() - 1.0f);
    }
}

void gGLInput::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;
    keyboard[event->key()] = KEY_STATE::KEY_UP;
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
