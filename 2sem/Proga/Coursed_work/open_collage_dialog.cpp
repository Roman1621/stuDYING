#include "open_collage_dialog.h"
#include "color.h"

collage_dialog::collage_dialog(Png *im, QWidget *parent) : QDialog(parent){
    collage_dialog::image = im;
    QVBoxLayout *group_texts = new QVBoxLayout();
    QLabel* text1 = new QLabel("Выберите N");
    QLabel* text2 = new QLabel("Введите M");

    collage_dialog::box_N = new QLineEdit;
    collage_dialog::box_M = new QLineEdit;

    collage_button = new QPushButton("COLLAGE");
    connect(collage_button, &QPushButton::clicked, this, &collage_dialog::collage_pic);

    box_N->setFixedWidth(100);
    box_M->setFixedWidth(100);

    group_texts->addWidget(text1);
    group_texts->addWidget(box_N);
    group_texts->addWidget(text2);
    group_texts->addWidget(box_M);
    group_texts->addWidget(collage_button);

    setLayout(group_texts);
    show();
}

void collage_dialog::collage_pic(){
    QString q_box_N = box_N->text();
    QString q_box_M = box_M->text();


    int N, M;
    bool check[2];
    N = q_box_N.toInt(&check[0]);
    M = q_box_M.toInt(&check[1]);

    if(!check[0] || !check[1] || N<0 || M<0){
        QMessageBox::warning(this, tr("THE TITLE"), tr("Некорректный ввод размера"));
        return;
    }

    image->collage(N, M);
    QImage our_image = image->create_image();
    parent_window->pixmap.convertFromImage(our_image);
    parent_window->label->setPixmap(parent_window->pixmap);
}

QPushButton* collage_dialog::return_button()
{
    return collage_button;
}
