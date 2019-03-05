#ifndef GRENDERWIDGET_H
#define GRENDERWIDGET_H

#include <QWidget>

namespace Ui {
class GRenderWidget;
}

class GRenderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GRenderWidget(QWidget *parent = 0);
    ~GRenderWidget();

private:
    Ui::GRenderWidget *ui;
};

#endif // GRENDERWIDGET_H
