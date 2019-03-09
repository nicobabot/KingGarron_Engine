#ifndef GRENDERWIDGET_H
#define GRENDERWIDGET_H

#include <QWidget>

namespace Ui {
class GRenderWidget;
}

class gComponentRender;

class GRenderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GRenderWidget(QWidget *parent = 0);
    ~GRenderWidget();

public slots:
    void ModifyShapeComponent(const QString&);

public:
    Ui::GRenderWidget *ui= nullptr;
    gComponentRender *renderComponent = nullptr;

};

#endif // GRENDERWIDGET_H
