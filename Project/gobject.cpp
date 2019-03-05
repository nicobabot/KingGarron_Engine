#include "gobject.h"
#include "gcomponent.h"
#include "gcomponenttransform.h"

gObject::gObject(QString name, bool active, QWidget *parent) : QWidget(parent), name(name), active(active)
{
    setAutoFillBackground(true);
    AddComponentTransform();
}

gObject::~gObject()
{
    for (gComponent* component : gComponentVector)
        delete component;
    gComponentVector.clear();
}

QSize gObject::sizeHint() const
{
    return QSize(256,256);
}

QSize gObject::minimumSizeHint() const
{
    return QSize(64,64);
}

void gObject::AddComponentTransform()
{
    gComponentVector.push_back(new gComponentTransform());
}

void gObject::AddComponentRenderShape()
{
    //gComponentVector.push_back(new gComponentRenderShape());
}

void gObject::paintEvent(QPaintEvent *)
{
    for (gComponent* component : gComponentVector)
    {
        //TODO call component paint method
    }
}
