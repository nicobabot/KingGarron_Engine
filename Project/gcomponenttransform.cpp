#include "gcomponent.h"
#include "gcomponenttransform.h"

gComponentTransform::gComponentTransform(gObject *parent): gComponent (parent)
{
    compType = gComponentType::COMP_TRANSFORM;
}

gComponentTransform::gComponentTransform(gObject *parent, QVector3D newpos, QVector3D newscale, QQuaternion newrotation): gComponent (parent)
{
    compType = gComponentType::COMP_TRANSFORM;
    position = newpos;
    scale = newscale;
    rotation = newrotation;
}
