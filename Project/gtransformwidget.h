#ifndef GTRANSFORMWIDGET_H
#define GTRANSFORMWIDGET_H

#include <QWidget>

namespace Ui {
class GTransformWidget;
}

class gComponentTransform;

class GTransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GTransformWidget(QWidget *parent = 0);
    ~GTransformWidget();
public slots:
    void PosXWidget(double item);
    void PosYWidget(double item);
    void PosZWidget(double item);

public:
    Ui::GTransformWidget *ui;
    gComponentTransform *transformComponent = nullptr;
};

#endif // GTRANSFORMWIDGET_H
