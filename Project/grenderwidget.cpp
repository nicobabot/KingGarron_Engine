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
#include "myopenglwidget.h"
#include <qopengltexture.h>
#include <qimage.h>
#include "submesh.h"

GRenderWidget::GRenderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GRenderWidget)
{
    ui->setupUi(this);

    LoadAllModelsRecursive("Models/");

    AddResourcesToUI();
    AddTexturesResourcesToUI();

    connect(ui->Shapebox,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyShapeComponent(const QString&)));


    connect(ui->Material1Box,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyTexture0(const QString&)));
    connect(ui->Material2Box,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyTexture1(const QString&)));
    connect(ui->Material3Box,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyTexture2(const QString&)));
    connect(ui->Material4Box,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyTexture3(const QString&)));
    connect(ui->Material5Box,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyTexture4(const QString&)));
    connect(ui->Material6Box,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyTexture5(const QString&)));
    connect(ui->Material7Box,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyTexture6(const QString&)));
    connect(ui->Material8Box,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyTexture7(const QString&)));
    connect(ui->Material9Box,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyTexture8(const QString&)));

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
      ui->Material1Box->addItem(resource.first);
      ui->Material2Box->addItem(resource.first);
      ui->Material3Box->addItem(resource.first);
      ui->Material4Box->addItem(resource.first);
      ui->Material5Box->addItem(resource.first);
      ui->Material6Box->addItem(resource.first);
      ui->Material7Box->addItem(resource.first);
      ui->Material8Box->addItem(resource.first);
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

void GRenderWidget::ModifyTexture0(const QString& texture)
{
    TestNumTexture(1,texture);
}

void GRenderWidget::ModifyTexture1(const QString& texture)
{
    TestNumTexture(2,texture);
}
void GRenderWidget::ModifyTexture2(const QString& texture)
{
    TestNumTexture(3,texture);
}
void GRenderWidget::ModifyTexture3(const QString& texture)
{
    TestNumTexture(4,texture);
}
void GRenderWidget::ModifyTexture4(const QString& texture)
{
    TestNumTexture(5,texture);
}
void GRenderWidget::ModifyTexture5(const QString& texture)
{
    TestNumTexture(6,texture);
}
void GRenderWidget::ModifyTexture6(const QString& texture)
{
    TestNumTexture(7,texture);
}
void GRenderWidget::ModifyTexture7(const QString& texture)
{
    TestNumTexture(8,texture);
}
void GRenderWidget::ModifyTexture8(const QString& texture)
{
    TestNumTexture(9,texture);
}
void GRenderWidget::ModifyTexture9(const QString& texture)
{
    TestNumTexture(10,texture);
}

void GRenderWidget::TestNumTexture(int num, const QString& texture)
{
    if(num < renderComponent->myMesh->submeshes.count())
    {
        renderComponent->material = texturesResources.value(texture).toStdString();
        qDebug("Texture loading %s", renderComponent->material.c_str());
        renderComponent->myMesh->submeshes[num]->textureOpenGL = new QOpenGLTexture(QImage(renderComponent->material.c_str()));
    }
}

void GRenderWidget::ModifyTextureComponent(const QString& text)
{
    if (renderComponent != nullptr)
    {
        renderComponent->material = texturesResources.value(text).toStdString();

        for(int i=0; i<renderComponent->myMesh->submeshes.count(); i++)
        {
            //if(renderComponent->myMesh->submeshes[i]->textureOpenGL != nullptr)
            //{
            renderComponent->myMesh->submeshes[i]->textureOpenGL = new QOpenGLTexture(QImage(renderComponent->material.c_str()).mirrored());
            //}
            //else
            //{
            //    qDebug("TextureOpenGL Nullptr");
            //}
        }

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
