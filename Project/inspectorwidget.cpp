#include "gtransformwidget.h"
#include "grenderwidget.h"
#include "gobject.h"
#include "gcomponenttransform.h"
#include "ui_gtransformwidget.h"
#include "gcomponentrender.h"
#include "ui_grenderwidget.h"

InspectorWidget::InspectorWidget(QWidget *parent) :
    QWidget(parent)
{
    transform = new GTransformWidget();
    render_widget = new GRenderWidget();
    QVBoxLayout *layout_temp = new QVBoxLayout();
    layout_temp->addWidget(transform);
    layout_temp->addWidget(render_widget);
    setLayout(layout_temp);
}

void InspectorWidget::UpdateInspectorValues(gObject *object)
{
    //QSignalBlocker posx_blocker(transform->ui->pos_x);
    if(object!=nullptr)
    {
        for(gComponent *comp: object->gComponentVector)
        {
            switch(comp->compType)
            {
            case gComponentType::COMP_UNDEFINED:
            {
                break;
            }
            case gComponentType::COMP_TRANSFORM:
            {
                transform->transformComponent = static_cast<gComponentTransform*>(comp);
                transform->ui->pos_x->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->position.x()));
                transform->ui->pos_y->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->position.y()));
                transform->ui->pos_z->setValue(static_cast<double>(static_cast<gComponentTransform*>(comp)->position.z()));
                break;
            }
            case gComponentType::COMP_RENDER:
            {
                render_widget->renderComponent = static_cast<gComponentRender*>(comp);
                QString* strShape = new QString(((static_cast<gComponentRender*>(comp))->shape).c_str());
                int combIndex = render_widget->ui->Shapebox->findText(*strShape);
                if ( combIndex != -1 ) // -1 for not found
                {
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
