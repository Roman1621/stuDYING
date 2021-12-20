#ifndef OPEN_FILTERS_H
#define OPEN_FILTERS_H

#include "mainwindow.h"
#include "color.h"
#include "image.h"

class brightness_dialog: public QDialog{
private:
    Png* image;
    QPushButton *bright;

public:
    brightness_dialog(Png *im, QWidget *parent);
    QPushButton* return_button();
    QLineEdit *box_brightness;

public slots:
    void brightness_on_pic();
};
#endif // OPEN_FILTERS_H
