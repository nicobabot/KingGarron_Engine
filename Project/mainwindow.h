#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class gObject;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

extern Ui::MainWindow* mainWindow;

#endif // MAINWINDOW_H
