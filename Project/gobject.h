#ifndef GOBJECT_H
#define GOBJECT_H

#include <QObject>
#include <QWidget>
#include "inspectorwidget.h"
#include "gcomponent.h"

class GScene;
//class gComponent;
//enum gComponentType;

class gObject : public QWidget
{
    Q_OBJECT
    friend class InspectorWidget;
public:
    explicit gObject(QString name, bool active, QWidget *parent = nullptr);
    ~gObject();
    void AddComponentTransform();
    void AddComponentRenderShape();
    gComponent* GetComponent(gComponentType type);
private:
    QString name = "";
    bool active = true;
    QVector<gComponent*> gComponentVector;
};

#endif // GOBJECT_H
