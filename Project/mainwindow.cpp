#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gobject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    //TODO: Also create the gObject...
}

void MainWindow::HierarchyRemove()
{
    qDeleteAll(ui->HierarchyList->selectedItems());
    //TODO: Also destroy the gObject...
}
