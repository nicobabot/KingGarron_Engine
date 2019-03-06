#include "inspectorwidget.h"
#include "gtransformwidget.h"
#include <QBoxLayout>
#include <qlayout.h>
#include <QSpacerItem>
#include "grenderwidget.h"
#include "gobject.h"
#include <QWidget>
#include "gcomponent.h"
#include "gcomponenttransform.h"
#include "ui_gtransformwidget.h"
#include "grenderwidget.h"
#include "ui_grenderwidget.h"

InspectorWidget::InspectorWidget(QWidget *parent) :
    QWidget(parent)
{
    transform = new GTransformWidget();
    render_widget = new GRenderWidget();

    QVBoxLayout *layout_temp = new QVBoxLayout();
    //QSpacerItem *spacer = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout_temp->addWidget(transform);
    layout_temp->addWidget(render_widget);
    //layout_temp->addItem(spacer);

    setLayout(layout_temp);

}

void InspectorWidget::UpdateInspectorValues(gObject *object)
{
    if(object!=nullptr)
    {
        for(gComponent *comp: object->gComponentVector)
        {
            switch(comp->compType)
            {
            case gComponentType::COMP_UNDEFINED:
            {
                //Do nosin
             break;
            }
                case gComponentType::COMP_TRANSFORM:
            {
                transform->ui->pos_x->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->position.x()));
                transform->ui->pos_y->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->position.y()));
                transform->ui->pos_z->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->position.z()));
                break;
            }
            case gComponentType::COMP_RENDER:
            {
             //render_widget->ui->comboBox->addItem()
             break;
            }
            }
        }
    }
}

InspectorWidget::~InspectorWidget()
{

}
