#ifndef SEARCH_AND_DESTROY_DIALOG_H
#define SEARCH_AND_DESTROY_DIALOG_H

#include "mainwindow.h"
#include "color.h"
#include "image.h"

class search_and_destroy_dialog: public QDialog{
private:
    Png* image;
    color_rgba find_color, change_color;
    QPushButton *find_and_recolor_button;

public:
    search_and_destroy_dialog(Png* im, QWidget* parent);
    QLineEdit *box_N, *box_M;
    QPushButton* return_button();

public slots:
    void show_colour_list1();
    void show_colour_list2();
    void find_on_pic();
};

#endif // SEARCH_AND_DESTROY_DIALOG_H
