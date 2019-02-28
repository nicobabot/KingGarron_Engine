#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gobject.h"
#include"inspectorwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InspectorWidget *inspectorWidget = new InspectorWidget();
    ui->Inspector->setWidget(inspectorWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
