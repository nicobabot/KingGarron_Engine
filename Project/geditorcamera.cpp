#include "geditorcamera.h"
#include "myopenglwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gglinput.h"

gEditorCamera::gEditorCamera()
{

}

void gEditorCamera::Update()
{
    if (gGLInput* input = mainWindow->openGLWidget->inputClass)
    {
        if((input->GetKey(Qt::Key_W) == KEY_STATE::KEY_UP)||(input->GetKey(Qt::Key_W) == KEY_STATE::KEY_REPEAT))
            position.setZ(position.z() + camSpeed);
        if((input->GetKey(Qt::Key_S) == KEY_STATE::KEY_UP)||(input->GetKey(Qt::Key_S) == KEY_STATE::KEY_REPEAT))
            position.setZ(position.z() - camSpeed);
        if((input->GetKey(Qt::Key_A) == KEY_STATE::KEY_UP)||(input->GetKey(Qt::Key_A) == KEY_STATE::KEY_REPEAT))
            position.setX(position.x() + camSpeed);
        if((input->GetKey(Qt::Key_D) == KEY_STATE::KEY_UP)||(input->GetKey(Qt::Key_D) == KEY_STATE::KEY_REPEAT))
            position.setX(position.x() - camSpeed);
    }
}
