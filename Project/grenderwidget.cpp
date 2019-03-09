#include "grenderwidget.h"
#include "ui_grenderwidget.h"
#include "gcomponentrender.h"
#include "mainwindow.h"

GRenderWidget::GRenderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GRenderWidget)
{
    ui->setupUi(this);
    ui->Shapebox->addItem("Quad");
    ui->Shapebox->addItem("Circle");

    connect(ui->Shapebox,SIGNAL(currentTextChanged(const QString&)), this,SLOT(ModifyShapeComponent(const QString&)));
}

GRenderWidget::~GRenderWidget()
{
    delete ui;
}

void GRenderWidget::ModifyShapeComponent(const QString& text)
{
    renderComponent->shape = text.toStdString();
}
