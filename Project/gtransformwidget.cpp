#include "gtransformwidget.h"
#include "ui_gtransformwidget.h"

GTransformWidget::GTransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GTransformWidget)
{
    ui->setupUi(this);
}

GTransformWidget::~GTransformWidget()
{
    delete ui;
}
