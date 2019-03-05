#ifndef GOBJECT_H
#define GOBJECT_H

#include <QObject>
#include <QWidget>

class gComponent;
class GScene;

class gObject : public QWidget
{
    Q_OBJECT
public:
    explicit gObject(QString name, bool active, QWidget *parent = nullptr);
    ~gObject();

    void AddComponentTransform();
    void AddComponentRenderShape();

    void PaintGGObject(GScene* obj, QRect rect);

signals:

public slots:

private:
    QString name = "";
    bool active = true;
    QVector<gComponent*> gComponentVector;

};

#endif // GOBJECT_H
