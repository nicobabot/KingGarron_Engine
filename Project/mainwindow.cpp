#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gobject.h"
#include "inspectorwidget.h"
#include <qmimedata.h>
#include <QList>
#include <QUrl>
#include <QFileInfo>
#include <mesh.h>
#include <gobject.h>
#include <gcomponentrender.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWindow = new Ui::MainWindow;
    mainWindow->setupUi(this);

    setAcceptDrops(true);

}

MainWindow::~MainWindow()
{
    delete mainWindow;
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    qDebug("Enter File Type process");

    //QList<QUrl> urlList;
    bool ret = DetectValidFiles(event->mimeData()->urls());

    if(ret)
    event->accept();

}
bool MainWindow::DetectValidFiles(QList<QUrl> myList)
{
    bool ret = true;

    for(QUrl url: myList)
    {
        QFileInfo file;
        file.setFile(url.path());
        QString extension = file.completeSuffix();
        qDebug("The extension is: %s", extension.toStdString().c_str());

        if(extension.compare("obj") != 0 && extension.compare("fbx") != 0)
        {
           ret = false;
        }

    }

    return ret;
}

void MainWindow::dropEvent(QDropEvent* event)
{
    qDebug("React To File drop");

    QList<QUrl> myList = event->mimeData()->urls();

    Mesh* myMesh = nullptr;

    for(QUrl url: myList)
    {
        myMesh = new Mesh();
        qDebug("My path: %s", url.path().toStdString().substr(1).c_str());
        myMesh->loadModel(url.path().toStdString().substr(1).c_str());
        std::string name = "Object_";
        name += std::to_string(mainWindow->openGLWidget->objectNum++);
         mainWindow->HierarchyList->addItem(QString(name.c_str()));
        gObject* newObject = new gObject(QString(name.c_str()), true);
        gComponentRender *render = (gComponentRender*)newObject->GetComponent(gComponentType::COMP_RENDER);
        if(render!=nullptr)
        {
            render->myMesh = myMesh;
        }
        mainWindow->openGLWidget->myObjectsScene.push_back(newObject);
    }

    mainWindow->openGLWidget->needUpdate = true;
    this->repaint();
}
