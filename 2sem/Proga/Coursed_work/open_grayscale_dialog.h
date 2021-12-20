#ifndef OPEN_GRAYSCALE_DIALOG_H
#define OPEN_GRAYSCALE_DIALOG_H

#include "mainwindow.h"
#include "color.h"
#include "image.h"

class grayscale_dialog: public QDialog{
private:
    Png* image;
    QPushButton *grayscale_button;

public:
    grayscale_dialog(Png *im, QWidget *parent);
    QPushButton* return_button();

public slots:
    void grayscale_on_pic();
};
#endif // OPEN_GRAYSCALE_DIALOG_H
