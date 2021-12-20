#include "mainwindow.h"
#include "draw_triangle_dialog.h"
#include "open_collage_dialog.h"
#include "search_and_destroy_dialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    quit = new QAction("Quit", this);
    open_png = new QAction("Open file", this);
    draw_triangle = new QAction("Triangle", this);
    search_and_destroy = new QAction("Find rectangle and recolor", this);
    collage = new QAction("Collage", this);
    brightness = new QAction("Brightness", this);
    negative = new QAction("Negative", this);
    grayscale = new QAction("Grayscale", this);
    save_png = new QAction("Save file", this);

    label = new QLabel;
    window = new QWidget;
    window->setLayout(new QHBoxLayout);
    window->layout()->addWidget(label);
    setCentralWidget(window);

    open_menu = menuBar()->addMenu("File");
    draw_menu = menuBar()->addMenu("Draw");
    quit_menu = menuBar()->addMenu("Quit");

    open_menu->addAction(open_png);
    open_menu->addAction(save_png);

    draw_menu->addAction(draw_triangle);
    draw_menu->addAction(search_and_destroy);
    draw_menu->addAction(collage);
    draw_menu->addAction(brightness);
    draw_menu->addAction(negative);
    draw_menu->addAction(grayscale);

    quit_menu->addAction(quit);

    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    connect(open_png, &QAction::triggered, this, &MainWindow::open_png_window);
    connect(draw_triangle, &QAction::triggered, this, &MainWindow::open_triangle_dialog);
    connect(search_and_destroy, &QAction::triggered, this, &MainWindow::open_sad_dialog);
    connect(collage, &QAction::triggered, this, &MainWindow::open_collage_dialog);
    connect(brightness, &QAction::triggered, this, &MainWindow::open_brightness_dialog);
    connect(negative, &QAction::triggered, this, &MainWindow::open_negative_dialog);
    connect(grayscale, &QAction::triggered, this, &MainWindow::open_grayscale_dialog);
    connect(save_png, &QAction::triggered, this, &MainWindow::save_png_window);
}

void MainWindow::open_png_window(){
    qadress = QFileDialog::getOpenFileName(this, "Open Dialog", "", tr("(*.png)"));
    QByteArray byte_array = qadress.toLocal8Bit();
    conv_adress = byte_array.data();

    try
    {
        image = new Png(conv_adress);
        check = true;
    }
    catch(const char* error)
    {
        QMessageBox::warning(this, tr("ERROR"), tr(error));
        return;
    }

    QImage our_image = image->create_image();
    pixmap.convertFromImage(our_image);
    label->setPixmap(pixmap);
}

void MainWindow::open_triangle_dialog(){
    draw_triangle_dialog* triangle_dialog = new draw_triangle_dialog(image, this);
    connect(triangle_dialog->return_button(), &QPushButton::clicked, this, &MainWindow::update_pixels);
    triangle_dialog->setWindowTitle("TRIANGLE");
}

void MainWindow::open_sad_dialog(){
    search_and_destroy_dialog* sad_dialog = new search_and_destroy_dialog(image, this);
    connect(sad_dialog->return_button(), &QPushButton::clicked, this, &MainWindow::update_pixels);
    sad_dialog->setWindowTitle("FIND AND RECOLOR");
}

void MainWindow::open_collage_dialog(){
    collage_dialog* col_dialog = new collage_dialog(image, this);
    connect(col_dialog->return_button(), &QPushButton::clicked, this, &MainWindow::update_pixels);
    col_dialog->setWindowTitle("COLLAGE");
    col_dialog->parent_window = this;
}

void MainWindow::open_brightness_dialog(){
    brightness_dialog* bright = new brightness_dialog(image, this);
    connect(bright->return_button(), &QPushButton::clicked, this, &MainWindow::update_pixels);
    bright->setWindowTitle("BRIGHTNESS");
}

void MainWindow::open_negative_dialog(){
    negative_dialog* neg = new negative_dialog(image, this);
    connect(neg->return_button(), &QPushButton::clicked, this, &MainWindow::update_pixels);
    neg->setWindowTitle("NEGATIVE");
}

void MainWindow::open_grayscale_dialog(){
    grayscale_dialog* gray = new grayscale_dialog(image, this);
    connect(gray->return_button(), &QPushButton::clicked, this, &MainWindow::update_pixels);
    gray->setWindowTitle("GRAYSCALE");
}
void MainWindow::save_png_window(){
    if(check){
        qadress_save = QFileDialog::getSaveFileName(this, "Save file", "");
        if(QString::compare(qadress_save, "")){
            QByteArray byte_array = qadress_save.toLocal8Bit();
            conv_save_adress = byte_array.data();
            try{
                image->save_png(conv_save_adress);
            }
            catch(const char* error){
                QMessageBox::warning(this, tr("ERROR"), tr(error));
                return;
            }
        }
    }
    else{
        QMessageBox::warning(this, tr("ERROR"), tr("You haven't opened file"));
    }
}

void MainWindow::update_pixels()
{
    QImage im = image->create_image();
    pixmap.convertFromImage(im);
    label->setPixmap(pixmap);
}
