#include "gcomponenttransform.h"

gComponentTransform::gComponentTransform()
{

}

gComponentTransform::gComponentTransform(QVector3D newpos, QVector3D newscale, QQuaternion newrotation)
{
    position = newpos;
    scale = newscale;
    rotation = rotation;
}
