#include "search_and_destroy_dialog.h"
#include "color.h"

search_and_destroy_dialog::search_and_destroy_dialog(Png *im, QWidget *parent) : QDialog(parent){
    search_and_destroy_dialog::image = im;
    QVBoxLayout *group_texts = new QVBoxLayout();
    QLabel* text1 = new QLabel("Выберите цвет, прямоугольник которого надо найти");
    QLabel* text2 = new QLabel("Введите цвет, в который надо перекрасить прямоугольник");

    QPushButton *choose_find_color = new QPushButton("Цвет искомого");
    QPushButton *choose_change_color = new QPushButton("Цвет перекраски");
    find_and_recolor_button = new QPushButton("FIND");

    connect(choose_find_color, &QPushButton::clicked, this, &search_and_destroy_dialog::show_colour_list1);
    connect(choose_change_color, &QPushButton::clicked, this, &search_and_destroy_dialog::show_colour_list2);
    connect(find_and_recolor_button, &QPushButton::clicked, this, &search_and_destroy_dialog::find_on_pic);

    group_texts->addWidget(text1);
    group_texts->addWidget(choose_find_color);
    group_texts->addWidget(text2);
    group_texts->addWidget(choose_change_color);
    group_texts->addWidget(find_and_recolor_button);

    setLayout(group_texts);
    show();
}

void search_and_destroy_dialog::find_on_pic(){
    image->search_and_destroy(find_color, change_color);
}

void search_and_destroy_dialog::show_colour_list1(){
    QColor colour = QColorDialog::getColor(Qt::white, this);
    find_color = color_rgba(colour.red(),colour.green(), colour.blue(), colour.alpha());
}

void search_and_destroy_dialog::show_colour_list2(){
    QColor colour = QColorDialog::getColor(Qt::white, this);
    change_color = color_rgba(colour.red(),colour.green(), colour.blue(), colour.alpha());
}

QPushButton* search_and_destroy_dialog::return_button()
{
    return find_and_recolor_button;
}
