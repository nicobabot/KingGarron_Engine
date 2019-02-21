#ifndef GPRIMITIVE_H
#define GPRIMITIVE_H

#include <QObject>
#include <QWidget>

class GPrimitive : public QWidget
{
    Q_OBJECT
public:
    explicit GPrimitive(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:

public slots:

private:
    void paintEvent(QPaintEvent *event) override;
};

#endif // GPRIMITIVE_H
