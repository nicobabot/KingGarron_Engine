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
    QWidget(parent), ui(new Ui::GRenderWidget)
{
    ui->setupUi(this);
    //-----------------------------------------------------------------------------------
    verticalLayout = new QVBoxLayout();
    //verticalLayout->setParent(ui->groupBox);
    shapeButton = new QLabel("shape", this);
    shapeComboBox = new QComboBox(this);
    connect(shapeComboBox, SIGNAL(currentTextChanged(const QString&)), this, SLOT(ModifyShapeComponent(const QString&)));
    QHBoxLayout* hBoxLayout = new QHBoxLayout();
    hBoxLayout->addWidget(shapeButton);
    hBoxLayout->addWidget(shapeComboBox);
    verticalLayout->addLayout(hBoxLayout);
    //------------------------------------------------------------------------------------
    modelResources.insert(QString("-"), QString("-"));
    texturesResources.insert(QString("-"), QString("-"));
    LoadAllModelsRecursive("Models/");
    AddResourcesToUI();
    ui->groupBox->setLayout(verticalLayout);
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
        else
        {
            QFileInfo file;
            file.setFile(infoList[i].filePath());
            QString extension = file.completeSuffix();
            //qDebug("The extension is: %s", extension.toStdString().c_str());
            if(extension.compare("obj") == 0 || extension.compare("fbx") == 0)
            {
                QString nameComplete = infoList[i].filePath();
                //qDebug("%s into model resources", infoList[i].fileName().toStdString().c_str());
                modelResources.insert(infoList[i].fileName(), nameComplete.toStdString().c_str());
            }
            else if(extension.compare("png") == 0 || extension.compare("jpg") == 0)
            {
                QString nameComplete = infoList[i].filePath();
                //qDebug("%s into model resources", infoList[i].fileName().toStdString().c_str());
                texturesResources.insert(infoList[i].fileName(), nameComplete.toStdString().c_str());
            }
        }
    }
}

void GRenderWidget::AddResourcesToUI()
{
    for(std::pair<QString,QString> resource : modelResources.toStdMap())
        shapeComboBox->addItem(resource.first);
}

void GRenderWidget::AddTexturesResourcesToUI()
{
    for (std::pair<QString,QString> resource : texturesResources.toStdMap())
        for (MaterialSelector& item : materialSelectorList)
            item.comboBox->addItem(resource.first);
}

void GRenderWidget::AddMaterialSelectors(Mesh* mesh)
{
    for (QList<MaterialSelector>::iterator item = materialSelectorList.begin(); item != materialSelectorList.end(); ++item)
    {
        verticalLayout->removeWidget(item->label);
        verticalLayout->removeWidget(item->comboBox);
        verticalLayout->removeItem(item->hLayout);
        item->Delete();
    }
    materialSelectorList.clear();
    verticalLayout->update();
    for (int i = 0; i < mesh->submeshes.length(); i++)
        AddButton(i, mesh->submeshes[i]);
}

void GRenderWidget::AddButton(int submeshnum, SubMesh* submesh)
{
    MaterialSelector selector;
    selector.label = new QLabel(submesh->name, this);
    selector.comboBox = new QComboBox(this);
    selector.comboBox->setObjectName(QString::fromStdString(std::to_string(submeshnum)));
    connect(selector.comboBox,SIGNAL(currentTextChanged(const QString&)), this, SLOT(ModifyTexture(const QString&)));
    selector.hLayout = new QHBoxLayout();
    selector.hLayout->addWidget(selector.label);
    selector.hLayout->addWidget(selector.comboBox);
    verticalLayout->addLayout(selector.hLayout);
    materialSelectorList.push_back(selector);
}

void GRenderWidget::ModifyShapeComponent(const QString& text)
{
    if (!renderComponent) return;
    renderComponent->shape = text.toStdString();
    renderComponent->myMesh->destroy();
    QString path = modelResources.value(text);
    renderComponent->myMesh->loadModel(path.toStdString().c_str());
    AddMaterialSelectors(renderComponent->myMesh);
    AddTexturesResourcesToUI();
    setLayout(verticalLayout);
}

void GRenderWidget::ModifyTexture(const QString& texture)
{
    //qDebug("Texture loading %s", texture.toStdString().c_str());
    //qDebug("Texture loading %s", sender()->objectName().toStdString().c_str());
    int index = std::stoi(sender()->objectName().toStdString());
    //qDebug("Texture loading %i", index);
    TestNumTexture(index, texture);
}

void GRenderWidget::TestNumTexture(int num, const QString& texture)
{
    if (renderComponent && renderComponent->myMesh)
        if(num < renderComponent->myMesh->submeshes.count())
        {
            renderComponent->material = texturesResources.value(texture).toStdString();
            qDebug("Texture loading %s", renderComponent->material.c_str());
            renderComponent->myMesh->submeshes[num]->textureOpenGL = new QOpenGLTexture(QImage(renderComponent->material.c_str()));
        }
}

void MaterialSelector::Delete()
{
    delete label;
    delete comboBox;
    delete hLayout;
}
