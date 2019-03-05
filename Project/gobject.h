#ifndef GOBJECT_H
#define GOBJECT_H

#include <QObject>
#include <QWidget>

class gComponent;

class gObject : public QWidget
{
    Q_OBJECT
public:
    explicit gObject(QString name, bool active, QWidget *parent = nullptr);
    ~gObject();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void AddComponentTransform();
    void AddComponentRenderShape();

signals:

public slots:

private:
    void paintEvent(QPaintEvent *event) override;

private:
    QString name = "";
    bool active = true;
    QVector<gComponent*> gComponentVector;

};

#endif // GOBJECT_H
