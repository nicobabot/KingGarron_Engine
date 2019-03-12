#ifndef GRENDERWIDGET_H
#define GRENDERWIDGET_H

#include <QWidget>

namespace Ui {
class GRenderWidget;
}

class gComponentRender;
class GScene;

class GRenderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GRenderWidget(QWidget *parent = 0);
    ~GRenderWidget();

public slots:
    void ModifyShapeComponent(const QString&);
    void ModifySizeComponent(double item);
    void ColorPicker();

public:
    Ui::GRenderWidget *ui= nullptr;
    gComponentRender *renderComponent = nullptr;
    GScene *scene = nullptr;

};

#endif // GRENDERWIDGET_H
