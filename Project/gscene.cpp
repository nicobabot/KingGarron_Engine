#include <QListWidget>
#include "gscene.h"
#include "gobject.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inspectorwidget.h"

GScene::GScene(QWidget *parent) : QWidget(parent)
{
}

QSize GScene::sizeHint() const
{
    return QSize(256,256);
}

QSize GScene::minimumSizeHint() const
{
    return QSize(64,64);
}

void GScene::paintEvent(QPaintEvent* event)
{
    for (gObject* object : scenegObjectVector)
        object->PaintGGObject(this);
}
