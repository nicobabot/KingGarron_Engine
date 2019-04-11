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
public:
    QVector<gObject*> scenegObjectVector;
private:
    int objectNum = 0;
};

#endif // GSCENE_H
