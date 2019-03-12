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
#include "gcomponentrender.h"
#include "grenderwidget.h"
#include "ui_grenderwidget.h"
#include <QSignalBlocker>
#include "gscene.h"


InspectorWidget::InspectorWidget(QWidget *parent) :
    QWidget(parent)
{
    transform = new GTransformWidget();
    render_widget = new GRenderWidget();

    QVBoxLayout *layout_temp = new QVBoxLayout();
    //QSpacerItem - ERROR!
    //QSpacerItem *spacer = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout_temp->addWidget(transform);
    layout_temp->addWidget(render_widget);
    //layout_temp->addItem(spacer);

    setLayout(layout_temp);

}

void InspectorWidget::UpdateInspectorValues(gObject *object, GScene* scene)
{
    /*
    QSignalBlocker posx_blocker(transform->ui->pos_x);
    QSignalBlocker posy_blocker(transform->ui->pos_y);
    QSignalBlocker posz_blocker(transform->ui->pos_z);
    */

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
                transform->scene = scene;
                transform->transformComponent = static_cast<gComponentTransform*>(comp);
                transform->ui->pos_x->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->position.x()));
                transform->ui->pos_y->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->position.y()));
                transform->ui->pos_z->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->position.z()));

                 //transform->ui->scale_x->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->scale.x()));
                 //transform->ui->scale_y->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->scale.y()));
                 //transform->ui->scale_z->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->scale.z()));

                 //For rotation we need to transform quaternion to euler ang
                break;
            }
            case gComponentType::COMP_RENDER:
            {
                render_widget->scene = scene;
                render_widget->renderComponent = static_cast<gComponentRender*>(comp);
                QString* strShape = new QString(((static_cast<gComponentRender*>(comp))->shape).c_str());
                int combIndex = render_widget->ui->Shapebox->findText(*strShape);
                if ( combIndex != -1 ) { // -1 for not found
                   render_widget->ui->Shapebox->setCurrentIndex(combIndex);
                   render_widget->ui->SizeValue->setValue(static_cast<double>(static_cast<gComponentRender*>(comp)->size));
                   render_widget->ui->ColorButton->setStyleSheet(QString("Background-Color: %0;").arg(static_cast<gComponentRender*>(comp)->color.name()));
                }

             break;
            }
            }
        }
    }
}

InspectorWidget::~InspectorWidget()
{

}
