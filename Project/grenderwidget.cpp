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

    //-----------------------------------------------------------------------------------
    QVBoxLayout* myVvox = new QVBoxLayout(this);
    myVvox->addLayout(ui->horizontalLayoutShape);

    QLabel *myLabel = new QLabel("suc0", this);
    QComboBox *myButton = new QComboBox(this);
    connect(myButton,SIGNAL(currentTextChanged(const QString&)), this, SLOT(ModifyTexture0(const QString&)));
    QHBoxLayout* myvox = new QHBoxLayout(this);
    myvox->addWidget(myLabel);
    myvox->addWidget(myButton);
    myVvox->addLayout(myvox);

    QLabel *myLabel0 = new QLabel("suc1", this);
    QComboBox *myButton0 = new QComboBox(this);
    QHBoxLayout* myvox0 = new QHBoxLayout(this);
    myvox0->addWidget(myLabel0);
    myvox0->addWidget(myButton0);
    myVvox->addLayout(myvox0);

    QSpacerItem* space = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    myVvox->addItem(space);

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
        /*
      ui->Material1Box->addItem(resource.first);
      ui->Material2Box->addItem(resource.first);
      ui->Material3Box->addItem(resource.first);
      ui->Material4Box->addItem(resource.first);
      ui->Material5Box->addItem(resource.first);
      ui->Material6Box->addItem(resource.first);
      ui->Material7Box->addItem(resource.first);
      ui->Material8Box->addItem(resource.first);*/
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

void GRenderWidget::ModifyTexture(const QString& texture)
{
    TestNumTexture(1,texture);
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
