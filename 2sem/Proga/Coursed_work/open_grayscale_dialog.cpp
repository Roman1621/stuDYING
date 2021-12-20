#include "open_grayscale_dialog.h"
#include "color.h"

grayscale_dialog::grayscale_dialog(Png *im, QWidget *parent) : QDialog(parent){
    grayscale_dialog::image = im;
    QVBoxLayout *temp = new QVBoxLayout();
    grayscale_button = new QPushButton("Сделать серым");

    connect(grayscale_button, &QPushButton::clicked, this, &grayscale_dialog::grayscale_on_pic);
    temp->addWidget(grayscale_button);
    setLayout(temp);
    show();
}

void grayscale_dialog::grayscale_on_pic(){
    image->grayscale();
}

QPushButton* grayscale_dialog::return_button()
{
    return grayscale_button;
}
