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

    connect(ui->scale_x, SIGNAL(valueChanged(double)), this, SLOT(ScaleXWidget(double)));
    connect(ui->scale_y, SIGNAL(valueChanged(double)), this, SLOT(ScaleYWidget(double)));
    connect(ui->scale_z, SIGNAL(valueChanged(double)), this, SLOT(ScaleZWidget(double)));

    connect(ui->rot_x, SIGNAL(valueChanged(double)), this, SLOT(RotXWidget(double)));
    connect(ui->rot_y, SIGNAL(valueChanged(double)), this, SLOT(RotYWidget(double)));
    connect(ui->rot_z, SIGNAL(valueChanged(double)), this, SLOT(RotZWidget(double)));
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

void GTransformWidget::ScaleXWidget(double item)
{
    if(transformComponent!=nullptr)
        transformComponent->scale.setX(static_cast<float>(item));
}
void GTransformWidget::ScaleYWidget(double item)
{
    if(transformComponent!=nullptr)
        transformComponent->scale.setY(static_cast<float>(item));
}
void GTransformWidget::ScaleZWidget(double item)
{
    if(transformComponent!=nullptr)
        transformComponent->scale.setZ(static_cast<float>(item));
}

void GTransformWidget::RotXWidget(double item)
{
    if(transformComponent!=nullptr)
    {
        transformComponent->UIrotation.setX(static_cast<float>(item));
        transformComponent->rotation = QQuaternion::fromEulerAngles(transformComponent->UIrotation);
    }
}
void GTransformWidget::RotYWidget(double item)
{
    if(transformComponent!=nullptr)
    {
        transformComponent->UIrotation.setY(static_cast<float>(item));
        transformComponent->rotation = QQuaternion::fromEulerAngles(transformComponent->UIrotation);
    }
}
void GTransformWidget::RotZWidget(double item)
{
    if(transformComponent!=nullptr)
    {
        transformComponent->UIrotation.setZ(static_cast<float>(item));
        transformComponent->rotation = QQuaternion::fromEulerAngles(transformComponent->UIrotation);
    }
}
