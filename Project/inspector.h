#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui {
class inspector;
}

class inspector : public QWidget
{
    Q_OBJECT

public:
    explicit inspector(QWidget *parent = 0);
    ~inspector();

private:
    Ui::inspector *ui;
};

#endif // INSPECTOR_H
