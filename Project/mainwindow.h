#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class gObject;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void HierarchyAdd();
    void HierarchyRemove();

private:
    Ui::MainWindow* ui = nullptr;
    QVector<gObject*> ScenegObjectVector;
    int objectNum = 0;
};

#endif // MAINWINDOW_H
