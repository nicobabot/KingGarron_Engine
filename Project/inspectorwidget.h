#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <QWidget>

class GTransformWidget;
class GRenderWidget;
class gObject;
class GScene;

class InspectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();
    void UpdateInspectorValues(gObject *object = nullptr);
public:
    GTransformWidget *transform = nullptr;
    GRenderWidget *render_widget = nullptr;
};

#endif // INSPECTORWIDGET_H
