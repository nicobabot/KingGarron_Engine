#include "gcomponent.h"
#include"gobject.h"
#include <QPainter>

gComponent::gComponent(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
}

QSize gComponent::sizeHint() const{
    return QSize(256,256);
}

QSize gComponent::minimumSizeHint() const{
    return QSize(64,64);
}

void gComponent::paintEvent(QPaintEvent *)
{

}
