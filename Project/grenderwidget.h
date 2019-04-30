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
    void TestNumTexture(int num,const QString& texture);

public slots:
    void ModifyShapeComponent(const QString&);
    void ModifyTexture(const QString&);

public:
    Ui::GRenderWidget *ui= nullptr;
    gComponentRender *renderComponent = nullptr;
    GScene *scene = nullptr;
    QMap<QString, QString> modelResources;
    QMap<QString, QString> texturesResources;

};

#endif // GRENDERWIDGET_H
