#ifndef GRENDERWIDGET_H
#define GRENDERWIDGET_H

#include <QWidget>
#include <QMap>

namespace Ui
{
class GRenderWidget;
}

class gComponentRender;
class GScene;

class GRenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GRenderWidget(QWidget *parent = nullptr);
    ~GRenderWidget();
public slots:
    void ModifyShapeComponent(const QString&);
    void ModifySizeComponent(double item);
    void ColorPicker();
public:
    Ui::GRenderWidget *ui= nullptr;
    gComponentRender *renderComponent = nullptr;
    GScene *scene = nullptr;
    QMap<QString, QString> modelResources;
};

#endif // GRENDERWIDGET_H
