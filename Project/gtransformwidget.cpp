#include "gtransformwidget.h"
#include "ui_gtransformwidget.h"
#include "gcomponenttransform.h"

GTransformWidget::GTransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GTransformWidget)
{
    ui->setupUi(this);
    connect(ui->pos_x, SIGNAL(valueChanged(double)), this, SLOT(PosXWidget(double)));
    connect(ui->pos_y, SIGNAL(valueChanged(double)), this, SLOT(PosYWidget(double)));
    connect(ui->pos_z, SIGNAL(valueChanged(double)), this, SLOT(PosZWidget(double)));
}

GTransformWidget::~GTransformWidget()
{
    delete ui;
}

void GTransformWidget::PosXWidget(double item)
{
    if (transformComponent != nullptr)
    {
        transformComponent->position.setX(item);
    }
}

void GTransformWidget::PosYWidget(double item)
{
    if(transformComponent!=nullptr)
    transformComponent->position.setY(item);
}

void GTransformWidget::PosZWidget(double item)
{
    if(transformComponent!=nullptr)
    transformComponent->position.setZ(item);
}
