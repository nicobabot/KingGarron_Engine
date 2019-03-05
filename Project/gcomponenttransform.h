#ifndef GCOMPONENTTRANSFORM_H
#define GCOMPONENTTRANSFORM_H
#include"gcomponent.h"
#include"qvector3d.h"
#include"qquaternion.h"

class gObject;

class gComponentTransform : public gComponent
{
public:
    gComponentTransform();
    gComponentTransform(QVector3D newpos, QVector3D newscale, QQuaternion newrotation);
public:
    QVector3D position;
    QVector3D scale;
    QQuaternion rotation;
};

#endif // GCOMPONENTTRANSFORM_H
