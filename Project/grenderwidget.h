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

    void LoadAllModelsRecursive(QString filename);
    void AddResourcesToUI();
    void AddTexturesResourcesToUI();

public slots:
    void ModifyShapeComponent(const QString&);
    void ModifyTextureComponent(const QString&);
    void ModifySizeComponent(double item);
    void ColorPicker();
public:
    Ui::GRenderWidget *ui= nullptr;
    gComponentRender *renderComponent = nullptr;
    GScene *scene = nullptr;
    QMap<QString, QString> modelResources;
    QMap<QString, QString> texturesResources;

};

#endif // GRENDERWIDGET_H
