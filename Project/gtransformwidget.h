#ifndef GTRANSFORMWIDGET_H
#define GTRANSFORMWIDGET_H

#include <QWidget>

namespace Ui {
class GTransformWidget;
}

class GTransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GTransformWidget(QWidget *parent = 0);
    ~GTransformWidget();

public:
    Ui::GTransformWidget *ui;
};

#endif // GTRANSFORMWIDGET_H
