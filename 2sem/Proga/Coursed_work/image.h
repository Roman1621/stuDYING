#ifndef IMAGE_H
#define IMAGE_H

#include <png.h>
#include <iostream>
#include <color.h>
#include <cstring>
#include <math.h>
#include <QImage>


class Png{
private:
    unsigned int rowb;
    int depth;
    int color;
    int weave;
    union{
        png_byte* raw;
        color_rgb* rgb;
        color_rgba* rgba;
    }data;

public:
    unsigned int w, h;
    Png(char adress[]);

    QImage create_image();

    color_rgb get_pixel_rgb(int x, int y);
    color_rgba get_pixel_rgba(int x, int y);

    void set_pixel_rgb(int x, int y, color_rgb color);
    void set_pixel_rgba(int x, int y, color_rgba color);

    void draw_line(int x1, int y1, int x2, int y2, color_rgba colour);
    void draw_thick_line(int x1, int y1, int x2, int y2, color_rgba colour, unsigned int thick);
    void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, color_rgba colour, unsigned int thick);
    void flat_bottom_triangle(int x1, int y1, int x2, int y2, int x3, int y3, color_rgba colour);
    void top_flat_bottom_triangle(int x1, int y1, int x2, int y2, int x3, int y3, color_rgba colour);
    void draw_flooded_triangle(int x1, int y1, int x2, int y2, int x3, int y3, color_rgba colour);
    void search_and_destroy(color_rgba find_colour, color_rgba change_colour);
    void collage(int N, int M);
    void brightness(double brightness);
    void negative();
    void grayscale();

    void save_png(char adress[]);
};

#endif // IMAGE_H
