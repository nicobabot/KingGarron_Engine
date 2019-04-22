#ifndef GCOMPONENTTRANSFORM_H
#define GCOMPONENTTRANSFORM_H
#include"gcomponent.h"
#include"qvector3d.h"
#include"qquaternion.h"

class gObject;

class gComponentTransform : public gComponent
{
public:
    gComponentTransform(gObject *parent);
    gComponentTransform(gObject *parent, QVector3D newpos, QVector3D newscale, QQuaternion newrotation);
public:
    QVector3D position = QVector3D(0.0f, 0.0f, 0.0f);
    QVector3D scale = QVector3D(1.0f, 1.0f, 1.0f);
    QQuaternion rotation = QQuaternion(0.0f, 0.0f, 0.0f, 0.0f);
};

#endif // GCOMPONENTTRANSFORM_H
