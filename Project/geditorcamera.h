#ifndef GEDITORCAMERA_H
#define GEDITORCAMERA_H

#include <QVector3D>

class gEditorCamera
{
public:
    gEditorCamera();
    void Update();

public:
    QVector3D position = QVector3D(0.0f, 0.0f, -3.0f);
    QVector3D reference = QVector3D(0.0f, 0.0f, 0.0f);
    QVector3D X = QVector3D(0.0f, 0.0f, 0.0f);
    QVector3D Y = QVector3D(0.0f, 0.0f, 0.0f);
    QVector3D Z = QVector3D(0.0f, 0.0f, 0.0f);
    float camSpeed = 0.01f;
};

#endif // GEDITORCAMERA_H
