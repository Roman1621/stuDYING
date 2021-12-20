#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QString>
#include <QMenu>
#include <QPushButton>
#include <QFileDialog>
#include <QAction>
#include <QMessageBox>
#include <QErrorMessage>
#include <QVBoxLayout>
#include <QDialog>
#include <QLineEdit>
#include <QWidget>
#include <QLayout>
#include <QPixmap>
#include <QMenuBar>
#include <QLabel>
#include <QColorDialog>
#include <QCheckBox>
#include <QDebug>

#include <iostream>
#include <cstring>

#include "draw_triangle_dialog.h"
#include "search_and_destroy_dialog.h"
#include "open_collage_dialog.h"
#include "png.h"
#include "image.h"
#include "open_brightness_dialog.h"
#include "open_negative_dialog.h"
#include "open_grayscale_dialog.h"

class MainWindow : public QMainWindow
{
private:
    QAction *open_png, *save_png, *quit, *draw_triangle, *search_and_destroy, *brightness, *negative, *grayscale, *collage;
    QMenu *open_menu, *quit_menu, *draw_menu;
    QWidget *window;
    QLayout *layout_compain;
    Png *image;
    char *conv_adress; //адрес на открытие и на сохранение
    char *conv_save_adress;

public:
    QLabel *label;
    QPixmap pixmap;
    MainWindow(QWidget *parent = nullptr);
    QString qadress;//возвращаемый адрес
    QString qadress_save;
    bool check = false;

private slots:
    void open_png_window();
    void save_png_window();
    void open_triangle_dialog();
    void open_sad_dialog();
    void open_collage_dialog();
    void open_brightness_dialog();
    void open_negative_dialog();
    void open_grayscale_dialog();

public slots:
    void update_pixels();
};
#endif // MAINWINDOW_H
