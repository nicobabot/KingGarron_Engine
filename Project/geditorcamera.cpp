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
    gGLInput* input = mainWindow->openGLWidget->inputClass;
    if (!input) return;
    QVector3D newPos = QVector3D(0.0f, 0.0f, 0.0f);
    if (input->GetKeyIsState(Qt::Key_W, KEY_STATE::KEY_REPEAT)) newPos += Z * camSpeed;
    if (input->GetKeyIsState(Qt::Key_S, KEY_STATE::KEY_REPEAT)) newPos -= Z * camSpeed;
    if (input->GetKeyIsState(Qt::Key_A, KEY_STATE::KEY_REPEAT)) newPos += X * camSpeed;
    if (input->GetKeyIsState(Qt::Key_D, KEY_STATE::KEY_REPEAT)) newPos -= X * camSpeed;
    if (input->GetKeyIsState(Qt::Key_Q, KEY_STATE::KEY_REPEAT)) newPos.setY(newPos.y() - camSpeed);
    if (input->GetKeyIsState(Qt::Key_E, KEY_STATE::KEY_REPEAT)) newPos.setY(newPos.y() + camSpeed);
    position += newPos;
    /*
    if (input->GetMouseButtonIsState(1, KEY_STATE::KEY_REPEAT))
    {
        qDebug("ROTATE");
        int dx = -input->GetMouseXMotion();
        int dy = -input->GetMouseYMotion();
        position -= reference;
        if (dx != 0)
        {
            float deltaX = static_cast<float>(dx) * sensitivity;
            QMatrix4x4 rotate;
            rotate.setToIdentity();
            rotate.rotate(deltaX, QVector3D(0.0f, 1.0f, 0.0f));
            X = rotate * X;
            Y = rotate * Y;
            Z = rotate * Z;
        }
        if (dy != 0)
        {
            float deltaY = static_cast<float>(dy) * sensitivity;
            QMatrix4x4 rotate;
            rotate.setToIdentity();
            rotate.rotate(deltaY, X);
            Y = rotate * Y;
            Z = rotate * Z;
            if (Y.y() < 0.0f)
            {
                Z = QVector3D(0.0f, Z.y() > 0.0f ? 1.0f : -1.0f, 0.0f);
                Y = QVector3D::crossProduct(Z, X);
            }
        }
        position = reference + -Z * position.length();
    }
    */
}
