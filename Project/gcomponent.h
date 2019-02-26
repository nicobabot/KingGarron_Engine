#ifndef GCOMPONENT_H
#define GCOMPONENT_H

#include <QObject>
#include <QWidget>

class gComponent : public QWidget
{
    Q_OBJECT
public:
    explicit gComponent(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:

public slots:

private:
    void paintEvent(QPaintEvent *event) override;
};

#endif // GCOMPONENT_H
