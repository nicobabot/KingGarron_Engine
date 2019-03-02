#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gobject.h"
#include "inspectorwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InspectorWidget *inspectorWidget = new InspectorWidget();
    ui->Inspector->setWidget(inspectorWidget);
    connect(ui->HierarchyAdd, SIGNAL(clicked()), this, SLOT(HierarchyAdd()));
    connect(ui->HierarchyRemove, SIGNAL(clicked()), this, SLOT(HierarchyRemove()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HierarchyAdd()
{
    std::string name = "Object_";
    name += std::to_string(objectNum++);
    ui->HierarchyList->addItem(QString(name.c_str()));
    scenegObjectVector.append(new gObject());
}

void MainWindow::HierarchyRemove()
{
    QModelIndexList indexes = ui->HierarchyList->selectionModel()->selectedIndexes();
    std::vector<int> indexList;
    for(QModelIndex index : indexes)
        indexList.push_back(index.row());
    for (int i = 0; i < static_cast<int>(indexList.size()); i++)
    {
        delete scenegObjectVector.at(i);
        scenegObjectVector.remove(i);
    }
    qDeleteAll(ui->HierarchyList->selectedItems());
}
