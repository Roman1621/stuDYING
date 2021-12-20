#ifndef OPEN_NEGATIVE_DIALOG_H
#define OPEN_NEGATIVE_DIALOG_H

#include "mainwindow.h"
#include "color.h"
#include "image.h"

class negative_dialog: public QDialog{
private:
    Png* image;
    QPushButton *negative_button;

public:
    negative_dialog(Png *im, QWidget *parent);
    QPushButton* return_button();

public slots:
    void negative_on_pic();
};
#endif // OPEN_NEGATIVE_DIALOG_H
