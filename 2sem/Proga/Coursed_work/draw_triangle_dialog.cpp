#include "draw_triangle_dialog.h"
#include "color.h"

draw_triangle_dialog::draw_triangle_dialog(Png* im, QWidget* parent) : QDialog(parent){
    draw_triangle_dialog::image = im;
    QVBoxLayout *group_box = new QVBoxLayout();
    QLabel* text1 = new QLabel("Введите координаты 1 вершины");
    QLabel* text2 = new QLabel("Введите координаты 2 вершины");
    QLabel* text3 = new QLabel("Введите координату 3 вершины");
    QLabel* text4 = new QLabel("Толщина");
    QLabel* text5 = new QLabel("Выберите цвет");

    draw_triangle_dialog::box_1 = new QLineEdit;
    draw_triangle_dialog::box_2 = new QLineEdit;
    draw_triangle_dialog::box_3 = new QLineEdit;
    draw_triangle_dialog::line_width = new QLineEdit;
    QPushButton *choose_colour = new QPushButton("Цвет");
    draw_triangle_button = new QPushButton("DRAW");

    check_box_for_fill = new QCheckBox("Залить треугольник");

    connect(choose_colour, &QPushButton::clicked, this, &draw_triangle_dialog::show_colour_list);
    connect(draw_triangle_button, &QPushButton::clicked, this, &draw_triangle_dialog::draw_triangle_on_pic);

    box_1->setFixedWidth(100);
    box_2->setFixedWidth(100);
    box_3->setFixedWidth(100);
    line_width->setFixedWidth(100);
    choose_colour->setFixedWidth(100);

    group_box->addWidget(text1);
    group_box->addWidget(box_1);
    group_box->addWidget(text2);
    group_box->addWidget(box_2);
    group_box->addWidget(text3);
    group_box->addWidget(box_3);
    group_box->addWidget(text4);
    group_box->addWidget(line_width);
    group_box->addWidget(text5);
    group_box->addWidget(choose_colour);
    group_box->addWidget(check_box_for_fill);
    group_box->addWidget(draw_triangle_button);

    setLayout(group_box);
    show();
}

void draw_triangle_dialog::draw_triangle_on_pic()
{
    QStringList q_box_1 = box_1->text().split(QLatin1Char(','));
    QStringList q_box_2 = box_2->text().split(QLatin1Char(','));
    QStringList q_box_3 = box_3->text().split(QLatin1Char(','));
    QString q_line_width = line_width->text();

    if(q_box_1.size() <= 1 || q_box_2.size() <= 1 || q_box_3.size() <= 1 || q_box_1.size() >= 3 || q_box_2.size() >=3 || q_box_3.size() >=3){
        QMessageBox::warning(this, tr("THE TITLE"), tr("Некорректный ввод координат"));
        return;
    }

    bool check[7];
    int x1, y1, x2, y2, x3, y3;
    int un_line_width;
    x1 = q_box_1[0].toInt(&check[0]);
    y1 = q_box_1[1].toInt(&check[2]);
    x2 = q_box_2[0].toInt(&check[1]);
    y2 = q_box_2[1].toInt(&check[3]);
    x3 = q_box_3[0].toInt(&check[4]);
    y3 = q_box_3[1].toInt(&check[5]);
    un_line_width = q_line_width.toInt(&check[6]);


    if(!check[0] || !check[1] || !check[2] || !check[3] || !check[4] || !check[5] ||
            x1<0 || x2<0 || y1<0 || y2<0 || x3<0 || y3 < 0 ||
            x1 > (int)image->w || x2 > (int)image->w || x3 > (int)image->w || y1 > (int)image ->h || y2 > (int)image->h || y3 > (int)image->h){
        QMessageBox::warning(this, tr("THE TITLE"), tr("Некорректный ввод координат"));
        return;
    }

    if(!QString::compare(q_line_width, ""))
        un_line_width = 2;
    else if(!check[6] || un_line_width <= 0 || un_line_width > (int)image->w || q_line_width > (int)image->h){
        QMessageBox::warning(this, tr("THE TITLE"), tr("Некорректный ввод толщины"));
        return;
    }

    if(check_box_for_fill->checkState())
        image->draw_flooded_triangle(x1, y1, x2, y2, x3, y3, triangle_color);
    else
        image->draw_triangle(x1, y1, x2, y2, x3, y3, triangle_color, un_line_width);
}

void draw_triangle_dialog::show_colour_list(){
    QColor colour = QColorDialog::getColor(Qt::white, this);
    triangle_color = color_rgba(colour.red(),colour.green(), colour.blue(), colour.alpha());
}

QPushButton* draw_triangle_dialog::return_button(){
    return draw_triangle_button;
}
