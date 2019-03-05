#include "gobject.h"
#include "gcomponent.h"
#include "gcomponentrender.h"

gObject::gObject(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
}

QSize gObject::sizeHint() const
{
    return QSize(256,256);
}

QSize gObject::minimumSizeHint() const
{
    return QSize(64,64);
}

void gObject::paintEvent(QPaintEvent *)
{
    for (gComponent* component : gComponentVector)
    {
        if(component->compType == gComponentType::COMP_RENDER)
            ((gComponentRender*)component)->gPaintObject(this, rect());
    }
}
