#ifndef GEDITORCAMERA_H
#define GEDITORCAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class gEditorCamera
{
public:
    gEditorCamera();
    void Update();

public:
    QVector3D position = QVector3D(0.0f, 0.0f, -3.0f);
    QVector3D reference = QVector3D(0.0f, 0.0f, 0.0f);
    QVector3D X = QVector3D(1.0f, 0.0f, 0.0f);
    QVector3D Y = QVector3D(0.0f, 1.0f, 0.0f);
    QVector3D Z = QVector3D(0.0f, 0.0f, 1.0f);
    float camSpeed = 0.01f;
    float sensitivity = 0.05f;
/*
public:
    gEditorCamera();
    QVector3D ScreenPointToWorldRay(int x, int y);
    QVector2D WorldToScreenPoint(const QVector3D& point);
    void CalcWorldViewMatrices();
    void CalcProjMatrix();

public:
    float fovy = 60.0f;
    float znear = 0.0f;
    float zfar = 0.0f;

    float yaw = 0.0f;
    float pitch 0.0f;
    QVector position = QVector3D(0.0f, 0.0f, -3.0f);
    float camSpeed = 0.01f;

    QMatrix4x4 worldMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projMatrix;
*/
};

#endif // GEDITORCAMERA_H
