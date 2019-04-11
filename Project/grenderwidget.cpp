#include "grenderwidget.h"
#include "ui_grenderwidget.h"
#include "gcomponentrender.h"
#include "mainwindow.h"
#include "gscene.h"
#include <QColorDialog>
#include "mesh.h"

GRenderWidget::GRenderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GRenderWidget)
{
    ui->setupUi(this);
    //modelResources = new QMap<QString, QString>();

    modelResources.insert("PalmTree",
    "C:/Users/nicolasba1/Desktop/PG/GARRONPARATI/kINGgARRON_eNGINE/KingGarron_Engine/Project/Models/PalmTree/PalmTree.obj");

    modelResources.insert("Patrick",
    "C:/Users/nicolasba1/Desktop/PG/GARRONPARATI/kINGgARRON_eNGINE/KingGarron_Engine/Project/Models/Patrick/Patrick.obj");

    ui->Shapebox->addItem("Patrick");
    ui->Shapebox->addItem("PalmTree");

    connect(ui->Shapebox,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyShapeComponent(const QString&)));
    connect(ui->SizeValue, SIGNAL(valueChanged(double)), this, SLOT(ModifySizeComponent(double)));
    connect(ui->ColorButton, SIGNAL(clicked()), this, SLOT(ColorPicker()));
}

GRenderWidget::~GRenderWidget()
{
    delete ui;
}

void GRenderWidget::ModifyShapeComponent(const QString& text)
{
    if (renderComponent != nullptr)
    {
        renderComponent->shape = text.toStdString();
        //renderComponent->myMesh->destroy();
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
