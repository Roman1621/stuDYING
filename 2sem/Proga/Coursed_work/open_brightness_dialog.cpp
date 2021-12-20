#include "open_brightness_dialog.h"
#include "color.h"

brightness_dialog::brightness_dialog(Png *im, QWidget *parent) : QDialog(parent){
    brightness_dialog::image = im;
    QVBoxLayout *group_texts = new QVBoxLayout();
    QLabel* text1 = new QLabel("Введите яркость");

    brightness_dialog::box_brightness = new QLineEdit;

    bright = new QPushButton("Изменить яркость картинки");

    connect(bright, &QPushButton::clicked, this, &brightness_dialog::brightness_on_pic);

    box_brightness->setFixedWidth(100);

    group_texts->addWidget(text1);
    group_texts->addWidget(box_brightness);
    group_texts->addWidget(bright);

    setLayout(group_texts);
    show();
}

void brightness_dialog::brightness_on_pic(){
    QString q_box_brightness = box_brightness->text();

    double brightness;
    bool check[1];
    brightness = q_box_brightness.toDouble(&check[0]);

    if(!check[0] || brightness<0){
        QMessageBox::warning(this, tr("THE TITLE"), tr("Некорректный ввод яркости"));
        return;
    }
    image->brightness(brightness);
}

QPushButton* brightness_dialog::return_button()
{
    return bright;
}
