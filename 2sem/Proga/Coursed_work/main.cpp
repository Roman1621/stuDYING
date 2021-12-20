#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(250, 150);
    w.setWindowTitle("Png_Editor");
    w.show();
    return a.exec();
}
