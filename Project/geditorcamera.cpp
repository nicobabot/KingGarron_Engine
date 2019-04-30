#include "geditorcamera.h"
#include "myopenglwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gglinput.h"
#include <qmath.h>

gEditorCamera::gEditorCamera()
{
    worldMatrix.setToIdentity();
    viewMatrix.setToIdentity();
    projMatrix.setToIdentity();
}

void gEditorCamera::Update()
{
    gGLInput* input = mainWindow->openGLWidget->inputClass;
    if (!input) return;

    QVector3D difVec = QVector3D(0.0f, 0.0f, 0.0f);
    if (input->GetKeyIsState(Qt::Key_W, KEY_STATE::KEY_REPEAT))
    {
        difVec = QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                    sinf(qDegreesToRadians(pitch)),
                    -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
        difVec *= DT * camSpeed;
    }
    else if(input->GetKeyIsState(Qt::Key_S, KEY_STATE::KEY_REPEAT))
    {
        difVec += QVector3D(sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                            -sinf(qDegreesToRadians(pitch)),
                            cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
        difVec *= DT * camSpeed;
    }
    else if(input->GetKeyIsState(Qt::Key_A, KEY_STATE::KEY_REPEAT))
    {
        difVec += QVector3D(-cosf(qDegreesToRadians(yaw)),
                            0.0f,
                            sinf(qDegreesToRadians(yaw)));
        difVec *= DT * camSpeed;
    }
    else if(input->GetKeyIsState(Qt::Key_D, KEY_STATE::KEY_REPEAT))
    {
        difVec += QVector3D(cosf(qDegreesToRadians(yaw)),
                            0.0f,
                            -sinf(qDegreesToRadians(yaw)));
        difVec *= DT * camSpeed;
    }
    position += difVec;

    //Mouse move
    if (input->GetMouseButtonIsState(1, KEY_STATE::KEY_REPEAT))
    {
        int dx = input->GetMouseXMotion();
        int dy = input->GetMouseYMotion();
        if ((dx != 0) || (dy != 0))
        {
            yaw -= camRotSpeed * dx * DT;
            pitch -= camRotSpeed * dy * DT;
            while (yaw < 0.0f) yaw += 360.0f;
            while (yaw > 360.0f) yaw -= 360.0f;
            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;
        }
        if (input->GetMouseZMotion())
        {
            camSpeed += input->GetMouseZMotion() * 1.0f;
        }
    }
    else
    {
        if (input->GetMouseZMotion())
        {
            QVector3D disVec = QVector3D(0.0f, 0.0f, 0.0f);
            if(input->GetMouseZMotion() > 0)
            {
                disVec += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                    sinf(qDegreesToRadians(pitch)),
                                    -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
                disVec *= DT * camScrollSpeed;
            }
            else if(input->GetMouseZMotion() < 0)
            {
                disVec += QVector3D(sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                    -sinf(qDegreesToRadians(pitch)),
                                    cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
                disVec *= DT * camScrollSpeed;
            }
            position += disVec;
        }
    }
}

QVector3D gEditorCamera::ScreenPointToWorldRay(int x, int y)
{
    return QVector3D(0.0f, 0.0f, 0.0f);
}

QVector2D gEditorCamera::WorldToScreenPoint(const QVector3D& point)
{
    return QVector2D(0.0f, 0.0f);
}

void gEditorCamera::CalcWorldViewMatrices()
{
    worldMatrix.setToIdentity();
    worldMatrix.translate(position);
    worldMatrix.rotate(yaw, QVector3D(0.0f,1.0f,0.0f));
    worldMatrix.rotate(pitch, QVector3D(1.0f,0.0f,0.0f));
    viewMatrix = worldMatrix.inverted();
}

void gEditorCamera::CalcProjMatrix(int width, int height)
{
    projMatrix.setToIdentity();
    projMatrix.perspective(fovy, static_cast<float>(width) / static_cast<float>(height), znear, zfar);
}
