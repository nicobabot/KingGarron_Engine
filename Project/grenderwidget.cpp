#include "grenderwidget.h"
#include "ui_grenderwidget.h"
#include "gcomponentrender.h"
#include "mainwindow.h"
#include "gscene.h"
#include <QColorDialog>
#include "mesh.h"
#include <QtDebug>
#include <QFile>
#include <qdir.h>


GRenderWidget::GRenderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GRenderWidget)
{
    ui->setupUi(this);

    LoadAllModelsRecursive("D:/CITM/4rto/Prog Grafica/KingGarron/KingGarron_Engine/Project/Models/");

    AddResourcesToUI();
    AddTexturesResourcesToUI();

    connect(ui->Shapebox,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyShapeComponent(const QString&)));
    connect(ui->SizeValue, SIGNAL(valueChanged(double)), this, SLOT(ModifySizeComponent(double)));
    connect(ui->ColorButton, SIGNAL(clicked()), this, SLOT(ColorPicker()));
}

GRenderWidget::~GRenderWidget()
{
    delete ui;
}

void GRenderWidget::LoadAllModelsRecursive(QString filename)
{

    QDir dir(filename);
    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList infoList = dir.entryInfoList();

    //qDebug("Num of path inside dir: %i", infoList.length());

    for(int i=0; i<infoList.length(); i++)
    {
         //qDebug("Path: %s", infoList[i].filePath().toStdString().c_str());

        if(infoList[i].isDir())
            LoadAllModelsRecursive(infoList[i].filePath());
        else{

            QFileInfo file;
            file.setFile(infoList[i].filePath());
            QString extension = file.completeSuffix();
            //qDebug("The extension is: %s", extension.toStdString().c_str());

            if(extension.compare("obj") == 0 || extension.compare("fbx") == 0)
            {
                QString nameComplete = infoList[i].filePath();
                qDebug("%s into model resources", infoList[i].fileName().toStdString().c_str());
                modelResources.insert(infoList[i].fileName(), nameComplete.toStdString().c_str());
            }
            else if(extension.compare("png") == 0 || extension.compare("jpg") == 0)
            {
                QString nameComplete = infoList[i].filePath();
                qDebug("%s into model resources", infoList[i].fileName().toStdString().c_str());
                texturesResources.insert(infoList[i].fileName(), nameComplete.toStdString().c_str());

            }
        }
    }

}

void GRenderWidget::AddResourcesToUI()
{

    for(std::pair<QString,QString> resource : modelResources.toStdMap())
    {
      //qDebug("%s added to UI", resource.first.toStdString().c_str());
      ui->Shapebox->addItem(resource.first);
    }

}

void GRenderWidget::AddTexturesResourcesToUI()
{

    for(std::pair<QString,QString> resource : texturesResources.toStdMap())
    {
      //qDebug("%s added to UI", resource.first.toStdString().c_str());
      ui->Materialbox->addItem(resource.first);
    }

}

void GRenderWidget::ModifyShapeComponent(const QString& text)
{
    if (renderComponent != nullptr)
    {
        renderComponent->shape = text.toStdString();
        renderComponent->myMesh->destroy();
        QString path = modelResources.value(text);
        renderComponent->myMesh->loadModel(path.toStdString().c_str());
    }
}

void GRenderWidget::ModifySizeComponent(double item)
{
    if(renderComponent!=nullptr)
        renderComponent->size = static_cast<float>(item);
    if (scene != nullptr)
        scene->repaint();
    else
        qDebug("Scene is nullptr");
}

void GRenderWidget::ColorPicker()
{
    QColor color = QColorDialog::getColor();
    if (renderComponent != nullptr)
    {
        renderComponent->color = color;
        ui->ColorButton->setStyleSheet(QString("Background-Color: %0;").arg(renderComponent->color.name()));
    }
    if (scene != nullptr)
        scene->repaint();
    else
        qDebug("Scene is nullptr");
}
