#include "open_negative_dialog.h"
#include "color.h"

negative_dialog::negative_dialog(Png *im, QWidget *parent) : QDialog(parent){
    negative_dialog::image = im;
    QVBoxLayout *temp = new QVBoxLayout();
    negative_button = new QPushButton("Сделать негативным");

    connect(negative_button, &QPushButton::clicked, this, &negative_dialog::negative_on_pic);
    temp->addWidget(negative_button);
    setLayout(temp);
    show();
}

void negative_dialog::negative_on_pic(){
    image->negative();
}

QPushButton* negative_dialog::return_button()
{
    return negative_button;
}
