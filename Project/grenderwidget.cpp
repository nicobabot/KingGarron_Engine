#include "grenderwidget.h"
#include "ui_grenderwidget.h"

GRenderWidget::GRenderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GRenderWidget)
{
    ui->setupUi(this);
}

GRenderWidget::~GRenderWidget()
{
    delete ui;
}
