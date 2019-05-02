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

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setParent(ui->groupBox);
    shapeButton = new QLabel("shape", this);
    shapeComboBox = new QComboBox(this);
    connect(shapeComboBox, SIGNAL(currentTextChanged(const QString&)), this, SLOT(ModifyShapeComponent(const QString&)));
    //connect(shapeComboBox,SIGNAL(currentTextChanged(const QString&)), this, SLOT(ModifyTexture(const QString&)));
    QHBoxLayout* hBoxLayout = new QHBoxLayout();
    hBoxLayout->addWidget(shapeButton);
    hBoxLayout->addWidget(shapeComboBox);
    verticalLayout->addLayout(hBoxLayout);

    //------------------------------------------------------------------------------------

    modelResources.insert(QString("-"), QString("-"));
    texturesResources.insert(QString("-"), QString("-"));
    LoadAllModelsRecursive("Models/");
    AddResourcesToUI();

    //------------------------------------------------------------------------------------
    /*
    QLabel* myLabel = new QLabel("suc0", this);
    QComboBox* myButton = new QComboBox(this);
    connect(myButton,SIGNAL(currentTextChanged(const QString&)), this, SLOT(ModifyTexture(const QString&)));
    QHBoxLayout* myvox = new QHBoxLayout();
    myvox->addWidget(myLabel);
    myvox->addWidget(myButton);
    verticalLayout->addLayout(myvox);

    QLabel* myLabel0 = new QLabel("suc1", this);
    QComboBox* myButton0 = new QComboBox(this);
    connect(myButton0,SIGNAL(currentTextChanged(const QString&)), this, SLOT(ModifyTexture(const QString&)));
    QHBoxLayout* myvox0 = new QHBoxLayout();
    myvox0->addWidget(myLabel0);
    myvox0->addWidget(myButton0);
    verticalLayout->addLayout(myvox0);

    //------------------------------------------------------------------------------------
    */
    //QSpacerItem* space = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    //verticalLayout->addItem(space);

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
    for(MaterialSelector& item : materialSelectorList)
        item.Delete();
    delete spacer;
    materialSelectorList.clear();
    for (int i = 0; i < mesh->submeshes.length(); i++)
        AddButton(mesh->submeshes[i]);
    spacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    verticalLayout->addItem(spacer);
}

void GRenderWidget::AddButton(SubMesh* submesh)
{
    MaterialSelector selector;
    selector.label = new QLabel("suc1", this);
    selector.comboBox = new QComboBox(this);
    connect(selector.comboBox,SIGNAL(currentTextChanged(const QString&)), this, SLOT(ModifyTexture(const QString&)));
    selector.hLayout = new QHBoxLayout();
    selector.hLayout->addWidget(selector.label);
    selector.hLayout->addWidget(selector.comboBox);
    verticalLayout->addLayout(selector.hLayout);
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
}

void GRenderWidget::ModifyTexture(const QString& texture)
{
    TestNumTexture(1,texture);
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
