#ifndef COLOR_H
#define COLOR_H

struct color_rgb
{
    color_rgb(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0): r (red), g (green), b (blue)
    {}
    unsigned char r, g, b;
};

struct color_rgba
{
    color_rgba(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0, unsigned char alpha = 255): r(red), g(green), b(blue), a(alpha)
    {}
    unsigned char r, g, b, a;
};

#endif // COLOR_H
