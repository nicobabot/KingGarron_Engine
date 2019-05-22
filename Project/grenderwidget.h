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
class QVBoxLayout;
class QHBoxLayout;
class QSpacerItem;
class QLabel;
class QComboBox;
class Mesh;
class SubMesh;
class QScrollArea;

struct MaterialSelector
{
    MaterialSelector() {}
    MaterialSelector(QLabel* label, QComboBox* comboBoxAlbedo, QHBoxLayout* hLayout) : label(label), comboBoxAlbedo(comboBoxAlbedo), hLayout(hLayout) {}
    void Delete();
    QLabel* label = nullptr;
    QComboBox* comboBoxAlbedo = nullptr;
    QHBoxLayout* hLayout = nullptr;
};

class GRenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GRenderWidget(QWidget *parent = nullptr);
    ~GRenderWidget();

    void LoadAllModelsRecursive(QString filename);
    void AddResourcesToUI();
    void AddTexturesResourcesToUI();
    void AddMaterialSelectors(Mesh* mesh);
    void AddButton(int submeshnum, SubMesh* submesh);

    bool eventFilter(QObject* obj, QEvent* eve);
    void adjustSize();

public slots:
    void ModifyShapeComponent(const QString&);
    void ModifyTextureAlbedo(const QString&);

public:
    Ui::GRenderWidget *ui= nullptr;
    gComponentRender *renderComponent = nullptr;
    GScene *scene = nullptr;
    QMap<QString, QString> modelResources;
    QMap<QString, QString> texturesResources;

    QWidget* contentWidget = nullptr;
    QScrollArea* scrollArea = nullptr;
    QVBoxLayout* verticalLayout = nullptr;
    QLabel* shapeButton = nullptr;
    QComboBox* shapeComboBox = nullptr;
    QSpacerItem* spacer = nullptr;
    QList<MaterialSelector> materialSelectorList;

};

#endif // GRENDERWIDGET_H
