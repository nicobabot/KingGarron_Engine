#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gobject.h"
#include "inspectorwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWindow = new Ui::MainWindow;
    mainWindow->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete mainWindow;
}
