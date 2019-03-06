#include <QListWidget>
#include "gscene.h"
#include "gobject.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inspectorwidget.h"

GScene::GScene(QWidget *parent) : QWidget(parent)
{
    inspectorWidget = new InspectorWidget();
    mainWindow->Inspector->setWidget(inspectorWidget);

    connect(mainWindow->HierarchyAdd, SIGNAL(clicked()), this, SLOT(HierarchyAdd()));
    connect(mainWindow->HierarchyRemove, SIGNAL(clicked()), this, SLOT(HierarchyRemove()));
    connect(mainWindow->HierarchyList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(HierarchyClicked(QListWidgetItem*)));
}

QSize GScene::sizeHint() const
{
    return QSize(256,256);
}

QSize GScene::minimumSizeHint() const
{
    return QSize(64,64);
}

void GScene::paintEvent(QPaintEvent *event)
{
    for (gObject* object : scenegObjectVector)
        object->PaintGGObject(this, rect());
    /*
    for (gComponent* component : gComponentVector)
    {
        if(component->compType == gComponentType::COMP_RENDER)
            ((gComponentRender*)component)->gPaintObject(obj, rect);
    }
    */
}

void GScene::HierarchyAdd()
{
    std::string name = "Object_";
    name += std::to_string(objectNum++);
    mainWindow->HierarchyList->addItem(QString(name.c_str()));
    scenegObjectVector.append(new gObject(QString(name.c_str()), true));
    this->repaint();
}

void GScene::HierarchyRemove()
{
    QModelIndexList indexes = mainWindow->HierarchyList->selectionModel()->selectedIndexes();
    std::vector<int> indexList;
    for(QModelIndex index : indexes)
        indexList.push_back(index.row());
    for (int i = 0; i < static_cast<int>(indexList.size()); i++)
    {
        delete scenegObjectVector.at(i);
        scenegObjectVector.remove(i);
    }
    qDeleteAll(mainWindow->HierarchyList->selectedItems());
    this->repaint();
}

void GScene::HierarchyClicked(QListWidgetItem* item)
{
    QModelIndexList indexes = mainWindow->HierarchyList->selectionModel()->selectedIndexes();
    indexes[0].row();
    //qDebug("SUCC");
}
