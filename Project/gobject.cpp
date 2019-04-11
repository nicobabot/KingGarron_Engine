#include "gobject.h"
//#include "gcomponent.h"
#include "gcomponentrender.h"
#include "gcomponenttransform.h"
#include "gscene.h"


gObject::gObject(QString name, bool active, QWidget *parent) : QWidget(parent), name(name), active(active)
{
    setAutoFillBackground(true);
    AddComponentTransform();
    AddComponentRenderShape();
}

gObject::~gObject()
{
    for (gComponent* component : gComponentVector)
        delete component;
    gComponentVector.clear();
}

void gObject::AddComponentTransform()
{
    gComponentVector.push_back(new gComponentTransform(this));
}

void gObject::AddComponentRenderShape()
{
    gComponentVector.push_back(new gComponentRender(this));
}

gComponent* gObject::GetComponent(gComponentType type)
{
    for (gComponent* component : gComponentVector)
        if(component->compType == type)
            return component;
    return nullptr;
}
