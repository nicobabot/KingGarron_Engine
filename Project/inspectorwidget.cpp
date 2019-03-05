#include "inspectorwidget.h"
#include "gtransformwidget.h"
#include <QBoxLayout>
#include <qlayout.h>
#include <QSpacerItem>
#include"grenderwidget.h"

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
InspectorWidget::~InspectorWidget()
{

}
