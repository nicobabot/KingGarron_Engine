#include "gtransformwidget.h"
#include "ui_gtransformwidget.h"
#include "gcomponenttransform.h"
#include "gscene.h"

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
        transformComponent->position.setX(static_cast<float>(item));
}

void GTransformWidget::PosYWidget(double item)
{
    if(transformComponent!=nullptr)
        transformComponent->position.setY(static_cast<float>(item));
}

void GTransformWidget::PosZWidget(double item)
{
    if(transformComponent!=nullptr)
        transformComponent->position.setZ(static_cast<float>(item));
}
