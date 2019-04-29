#ifndef GEDITORCAMERA_H
#define GEDITORCAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class gEditorCamera
{
public:
    gEditorCamera();
    void Update();
    QVector3D ScreenPointToWorldRay(int x, int y);
    QVector2D WorldToScreenPoint(const QVector3D& point);
    void CalcWorldViewMatrices();
    void CalcProjMatrix(int width, int height);

public:
    float fovy = 60.0f;
    float znear = 0.1f;
    float zfar = 10000.0f;

    float yaw = 0.0f;
    float pitch = 0.0f;
    QVector3D position = QVector3D(0.0f, 0.0f, 10.0f);
    float camSpeed = 1.0f;
    float camRotSpeed = 3.0f;

    QMatrix4x4 worldMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projMatrix;
};

#endif // GEDITORCAMERA_H
