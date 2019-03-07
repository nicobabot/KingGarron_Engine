#include "grenderwidget.h"
#include "ui_grenderwidget.h"

GRenderWidget::GRenderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GRenderWidget)
{
    ui->setupUi(this);
    ui->Shapebox->addItem("Quad");
    ui->Shapebox->addItem("Circle");

    connect(ui->Shapebox,SIGNAL(currentIndexChanged(const QString&)),
            this,SLOT(ModifyShapeComponent(const QString&)));
}

GRenderWidget::~GRenderWidget()
{
    delete ui;
}

void GRenderWidget::ModifyShapeComponent(QString* str)
{

}
