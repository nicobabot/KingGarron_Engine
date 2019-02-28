#include "inspectorwidget.h"
#include "gtransformwidget.h"
#include <QBoxLayout>
#include <qlayout.h>
#include <QSpacerItem>

InspectorWidget::InspectorWidget(QWidget *parent) :
    QWidget(parent)
{
    transform = new GTransformWidget();
    QVBoxLayout *layout_temp = new QVBoxLayout();
    layout_temp->addWidget(transform);
    setLayout(layout_temp);

}
InspectorWidget::~InspectorWidget()
{

}
