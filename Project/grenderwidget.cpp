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
#include <QScrollArea>

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
    //-----------------------------------------------------------------------------------
    contentWidget = new QWidget();
    contentWidget->setLayout(verticalLayout);
    contentWidget->installEventFilter(this);
    //-----------------------------------------------------------------------------------
    scrollArea = new QScrollArea();
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
    scrollArea->setWidget(contentWidget);
    scrollArea->setFrameStyle(QFrame::NoFrame);
    scrollArea->installEventFilter(this);
    ui->groupBox->layout()->addWidget(scrollArea);
    //------------------------------------------------------------------------------------
    modelResources.insert(QString("-"), QString("-"));
    texturesResources.insert(QString("-"), QString("-"));
    LoadAllModelsRecursive("Models/");
    AddResourcesToUI();
    adjustSize();
    //ui->groupBox->setLayout(verticalLayout);
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
        {
            QSignalBlocker block(item.comboBoxAlbedo);
            item.comboBoxAlbedo->addItem(resource.first);
        }
}

void GRenderWidget::AddMaterialSelectors(Mesh* mesh)
{
    for (QList<MaterialSelector>::iterator item = materialSelectorList.begin(); item != materialSelectorList.end(); ++item)
    {
        verticalLayout->removeWidget(item->label);
        verticalLayout->removeWidget(item->comboBoxAlbedo);
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
    selector.comboBoxAlbedo = new QComboBox(this);
    selector.comboBoxAlbedo->setObjectName(QString::fromStdString(std::to_string(submeshnum)));
    connect(selector.comboBoxAlbedo,SIGNAL(currentTextChanged(const QString&)), this, SLOT(ModifyTextureAlbedo(const QString&)));
    selector.hLayout = new QHBoxLayout();
    selector.hLayout->addWidget(selector.label);
    selector.hLayout->addWidget(selector.comboBoxAlbedo);
    verticalLayout->addLayout(selector.hLayout);
    materialSelectorList.push_back(selector);
}

bool GRenderWidget::eventFilter(QObject* obj, QEvent* eve)
{
    if (obj == scrollArea && eve->type() == QEvent::Resize)
        adjustSize();
    return false;
}

void GRenderWidget::adjustSize()
{
    QSignalBlocker blocker(contentWidget);
    int scrollWidth = scrollArea->width() - scrollArea->verticalScrollBar()->width();
    contentWidget->adjustSize();
    contentWidget->resize(scrollWidth, contentWidget->height());
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

void GRenderWidget::ModifyTextureAlbedo(const QString& texture)
{
    int index = std::stoi(sender()->objectName().toStdString());
    if (renderComponent && renderComponent->myMesh)
        if(index < renderComponent->myMesh->submeshes.count())
        {
            if (renderComponent->myMesh->submeshes[index]->OGLTexAlbedo)
                delete renderComponent->myMesh->submeshes[index]->OGLTexAlbedo;
            renderComponent->myMesh->submeshes[index]->OGLTexAlbedo = new QOpenGLTexture(QImage(texturesResources.value(texture).toStdString().c_str()));
        }
}

void MaterialSelector::Delete()
{
    delete label;
    delete comboBoxAlbedo;
    delete hLayout;
}
