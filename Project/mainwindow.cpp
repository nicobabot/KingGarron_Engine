#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gobject.h"
#include "inspectorwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWindow = new Ui::MainWindow;
    mainWindow->setupUi(this);
    InspectorWidget *inspectorWidget = new InspectorWidget();
    mainWindow->Inspector->setWidget(inspectorWidget);
}

MainWindow::~MainWindow()
{
    delete mainWindow;
}
