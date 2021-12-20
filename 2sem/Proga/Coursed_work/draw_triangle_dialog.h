#ifndef DRAW_TRIANGLE_DIALOG_H
#define DRAW_TRIANGLE_DIALOG_H

#include "mainwindow.h"
#include "color.h"
#include "image.h"

class draw_triangle_dialog : public QDialog{
private:
    Png *image;
    QCheckBox* check_box_for_fill;
    color_rgba triangle_color;
    QPushButton *draw_triangle_button;

public:
    draw_triangle_dialog(Png *im, QWidget* parent);
    QLineEdit *box_1, *box_2, *box_3, *line_width;
    QPushButton* return_button();

public slots:
    void show_triangle_dialog();
    void draw_triangle_on_pic();
    void show_colour_list();
};

#endif // DRAW_TRIANGLE_DIALOG_H
