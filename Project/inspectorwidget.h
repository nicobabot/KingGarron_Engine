#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <QWidget>

class GTransformWidget;

class InspectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();
signals:

public slots:

public:
        GTransformWidget *transform = nullptr;
};

#endif // INSPECTORWIDGET_H
