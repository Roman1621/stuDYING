#ifndef COLLAGE_DIALOG_H
#define COLLAGE_DIALOG_H

#include "mainwindow.h"
#include "color.h"
#include "image.h"

class MainWindow;

class collage_dialog: public QDialog{
private:
    Png* image;
    QPushButton *collage_button;

public:
    collage_dialog(Png* im, QWidget* parent);
    QPushButton* return_button();
    QLineEdit *box_N, *box_M;
    MainWindow* parent_window;

public slots:
    void collage_pic();
};

#endif // COLLAGE_DIALOG_H
