#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>

Ui::MainWindow* mainWindow = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
