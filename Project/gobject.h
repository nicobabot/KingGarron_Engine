#ifndef GOBJECT_H
#define GOBJECT_H

#include <QObject>
#include <QWidget>

class gComponent;

class gObject : public QWidget
{
    Q_OBJECT
public:
    explicit gObject(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:

public slots:

private:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<gComponent*> gComponentVector;

};

#endif // GOBJECT_H
