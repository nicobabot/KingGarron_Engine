#ifndef GTRANSFORMWIDGET_H
#define GTRANSFORMWIDGET_H

#include <QWidget>

namespace Ui
{
class GTransformWidget;
}

class gComponentTransform;
class GScene;

class GTransformWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GTransformWidget(QWidget *parent = nullptr);
    ~GTransformWidget();
public slots:
    void PosXWidget(double item);
    void PosYWidget(double item);
    void PosZWidget(double item);

    void ScaleXWidget(double item);
    void ScaleYWidget(double item);
    void ScaleZWidget(double item);

    void RotXWidget(double item);
    void RotYWidget(double item);
    void RotZWidget(double item);

public:
    Ui::GTransformWidget *ui = nullptr;
    gComponentTransform *transformComponent = nullptr;
    GScene *scene = nullptr;
};

#endif // GTRANSFORMWIDGET_H
