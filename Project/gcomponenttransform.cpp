#include "gcomponent.h"
#include "gcomponenttransform.h"

gComponentTransform::gComponentTransform()
{
    compType = gComponentType::COMP_TRANSFORM;
}

gComponentTransform::gComponentTransform(QVector3D newpos, QVector3D newscale, QQuaternion newrotation)
{
    compType = gComponentType::COMP_TRANSFORM;
    position = newpos;
    scale = newscale;
    rotation = rotation;
}
