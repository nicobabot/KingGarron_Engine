#ifndef GSCENE_H
#define GSCENE_H

#include <QWidget>

class QListWidgetItem;
class gObject;
class InspectorWidget;

class GScene : public QWidget
{
    Q_OBJECT
public:
    explicit GScene(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
private:
    void paintEvent(QPaintEvent *event) override;
public slots:
    void HierarchyAdd();
    void HierarchyRemove();
    void HierarchyClicked(QListWidgetItem* item = nullptr);
public:
    QVector<gObject*> scenegObjectVector;
private:
    InspectorWidget *inspectorWidget = nullptr;
    int objectNum = 0;
    int clickedIndex = 0;
};

#endif // GSCENE_H
