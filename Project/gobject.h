#ifndef GOBJECT_H
#define GOBJECT_H

#include <QObject>
#include <QWidget>

class gObject : public QWidget
{
    Q_OBJECT
public:
    explicit gObject(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // GOBJECT_H