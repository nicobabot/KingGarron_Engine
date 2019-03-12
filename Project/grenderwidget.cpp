#include "grenderwidget.h"
#include "ui_grenderwidget.h"
#include "gcomponentrender.h"
#include "mainwindow.h"
#include "gscene.h"
#include <QColorDialog>

GRenderWidget::GRenderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GRenderWidget)
{
    ui->setupUi(this);
    ui->Shapebox->addItem("Quad");
    ui->Shapebox->addItem("Circle");

    connect(ui->Shapebox,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyShapeComponent(const QString&)));
    connect(ui->SizeValue, SIGNAL(valueChanged(double)), this, SLOT(ModifySizeComponent(double)));
    connect(ui->ColorButton, SIGNAL(clicked()), this, SLOT(ColorPicker()));
    //ColorButton
}

GRenderWidget::~GRenderWidget()
{
    delete ui;
}

void GRenderWidget::ModifyShapeComponent(const QString& text)
{
    if(renderComponent!=nullptr)
    renderComponent->shape = text.toStdString();

    if(scene != nullptr){
        scene->repaint();
    }
    else{
        qDebug("Scene is nullptr");
    }
}

void GRenderWidget::ModifySizeComponent(double item)
{
    if(renderComponent!=nullptr)
    renderComponent->size = item;

    if(scene != nullptr){
        scene->repaint();
    }
    else{
        qDebug("Scene is nullptr");
    }
}

void GRenderWidget::ColorPicker(){

QColor color = QColorDialog::getColor();

if(renderComponent!=nullptr){
renderComponent->color = color;
ui->ColorButton->setStyleSheet(QString("Background-Color: %0;").arg(renderComponent->color.name()));
}

if(scene != nullptr){
    scene->repaint();
}
else{
    qDebug("Scene is nullptr");
}

}
