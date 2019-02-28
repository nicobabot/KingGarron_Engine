#include "gcomponent.h"
#include"gobject.h"
#include <QPainter>
#include "gobject.h"

gComponent::gComponent(gObject *parent)
{
    this->parent = parent;
}

