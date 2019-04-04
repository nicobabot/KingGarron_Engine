#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>

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
    void dragEnterEvent(QDragEnterEvent* event) override;
    bool DetectValidFiles(QList<QUrl> myList);
    void dropEvent(QDropEvent* event) override;
};

extern Ui::MainWindow* mainWindow;

#endif // MAINWINDOW_H
