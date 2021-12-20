#include "image.h"
#include <QDebug>

Png::Png(char adress[]){
    FILE* file = fopen(adress, "rb");
    if(!file){
        throw "Не могу открыть файл";
    }

    unsigned char header[8];
    memset(header, 0, sizeof(header));
    fread(header, 1, 8, file);
    if(!png_check_sig(header, 8))
        throw "Неизвестный тип файла";

    png_structp png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr){
        throw "Структура не создана";
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);//информация о пнг-файле
    if (!info_ptr){
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        throw "Структура информации о файле не создана";
    }

    if(setjmp(png_jmpbuf(png_ptr))){
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        throw "Невозможно инициализировать ввод-вывод";
    }
    png_init_io(png_ptr, file); // инициализация вывода в файл
    png_set_sig_bytes(png_ptr, 8);

    if(setjmp(png_jmpbuf(png_ptr))){
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        throw "Невозможно получить информацию о файле";
    }
    png_read_info(png_ptr, info_ptr);

    if(setjmp(png_jmpbuf(png_ptr))){
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        throw "Невозможно считать чанк IHDR";
    }
    png_get_IHDR(png_ptr, info_ptr, &w, &h, &depth, &color, NULL, NULL, NULL);//отвечает за информацию об изображении
    //глубина цвета отвеачает за количество байт, необходимых для кодирования одного пикселя

    if(color != PNG_COLOR_TYPE_RGB && color != PNG_COLOR_TYPE_RGBA){
            throw "Неизвестный тип цвета";
    }

    png_bytep* rowb_ptr = new png_bytep[h];//массив указателей на каждую строку пнг-файла
    rowb = png_get_rowbytes(png_ptr, info_ptr);
    data.raw = new png_byte[rowb*h];//выделяет место под всё изображение
    for(unsigned int i = 0; i < h; i++)
            rowb_ptr[i] = data.raw + i * rowb;

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        throw "Не получилось считать файл";
    }
    png_read_image(png_ptr, rowb_ptr);

    delete[] rowb_ptr;
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(file);
}

color_rgb Png::get_pixel_rgb(int x, int y){
    if(x>=0 && y>=0 && (unsigned int)x<w && (unsigned int)y<h)
        return data.rgb[y*w + x];
    else
        throw "Координаты выходят за границу изображения";
}

color_rgba Png::get_pixel_rgba(int x, int y){
    if(x>=0 && y>=0 && (unsigned int)x<w && (unsigned int)y<h)
        return data.rgba[y*w + x];
    else
        throw "Координаты выходят за границу изображения";
}

void Png::set_pixel_rgb(int x, int y, color_rgb color)
{
    if(x>=0 && y>=0 && (unsigned int)x<w && (unsigned int)y<h)
        data.rgb[y*w +x] = color;
}

void Png::set_pixel_rgba(int x, int y, color_rgba color)
{
    if(x>=0 && y>=0 && (unsigned int)x<w && (unsigned int)y<h)
        data.rgba[y*w +x] = color;
}

void Png::draw_line(int x1, int y1, int x2, int y2, color_rgba colour){
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dy + dx, e2;//Начальное значение ошибки
    color_rgb rgbcolor = {colour.r, colour.g, colour.b};
    for(;;){
        switch(color){
        case PNG_COLOR_TYPE_RGB:
            set_pixel_rgb(x1, y1, rgbcolor);
            break;
        case PNG_COLOR_TYPE_RGBA:
            set_pixel_rgba(x1, y1, colour);
            break;
        }
        if(x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if(e2 >= dy){
            err += dy;
            x1 += sx;
        }
        if(e2 <= dx){
            err += dx;
            y1 += sy;
        }
    }
}

void Png::draw_thick_line(int x1, int y1, int x2, int y2, color_rgba colour, unsigned int thick){
    draw_line(x1, y1, x2, y2, colour);
    int dx, dy;
    dx = x2-x1;
    dy = y2 - y1;
    if((dx == 0 || fabs((double)dy/dx) >= 1) && dy != 0){ //Если линия крутая
        double amountx = (thick-1) * sqrt(dx * dx + dy*dy) / (2*fabs(dy));
        if(dy == 0) amountx = 0.0;
        for(int i=0; i<amountx; i++){
            draw_line((x1 - i) >= 0 ? (x1 - i) : 0, y1, (x2 - i) >= 0 ? (x2 - i) : 0, y2, colour);
            draw_line((x1+i) <= (int)(w-1) ? (x1+i) : (w-1), y1, (x2+i) <= (int)(w-1) ? (x2+i) : (w-1), y2, colour);
        }
    }
    else{ //Если линия пологая
        double amounty = (thick-1) * sqrt(dx*dx + dy*dy) / (2 * fabs(dx));
        if(dx == 0) amounty = 0.0;
        for(int i=0; i<amounty; i++){
            draw_line(x1, (y1 - i) >= 0 ? (y1 - i) : 0, x2, (y2 - i) >= 0 ? (y2 - i) : 0, colour);
            draw_line(x1, (y1+i) <= (int)(h-1) ? (y1+i) : (h-1), x2, (y2+i) <= (int)(h-1) ? (y2+i) : (h-1), colour);
        }
    }
}

void Png::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, color_rgba colour, unsigned int thick){
    draw_thick_line(x1, y1, x2, y2, colour, thick);
    draw_thick_line(x2, y2, x3, y3, colour, thick);
    draw_thick_line(x3, y3, x1, y1, colour, thick);
}

int comp(const void* a, const void* b){
    const int* x1 = (const int*) a;
    const int* y1 = x1+1;
    const int* x2 = (const int *) b;
    const int* y2 = x2+1;
    return (*y1-*y2);
}

void Png::flat_bottom_triangle(int x1, int y1, int x2, int y2, int x3, int y3, color_rgba colour){
    double invslope1 = (double)(x2 - x1) / (y2 - y1);
    double invslope2 = (double)(x3 - x1) / (y3 - y1);

    double curx1 = x1;
    double curx2 = x1;

    for(int y = y1; y<=y2; y++){
        draw_line(curx1, y, curx2, y, colour);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void Png::top_flat_bottom_triangle(int x1, int y1, int x2, int y2, int x3, int y3, color_rgba colour){
    double invslope1 = (double)(x3 - x1) / (y3 - y1);
    double invslope2 = (double)(x3 - x2) / (y3 - y2);

    double curx1 = x3;
    double curx2 = x3;

    for(int y = y3; y>=y2; y--){
        draw_line(curx1, y, curx2, y, colour);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void Png::draw_flooded_triangle(int x1, int y1, int x2, int y2, int x3, int y3, color_rgba colour){
    int x4 , y4;
    int tmp[6];
    tmp[0] = x1; tmp[1] = y1; tmp[2] = x2; tmp[3] = y2; tmp[4] = x3; tmp[5] = y3;
    qsort(tmp, 3, sizeof(int)*2, comp);
    x4 = tmp[0] + ((double)(tmp[3] - tmp[1])/(tmp[5] - tmp[1]))*(tmp[4] - tmp[0]);
    y4 = tmp[3];

    if(tmp[3] == tmp[5]){
        flat_bottom_triangle(tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5], colour);
    }
    else if(tmp[1] == tmp[3]){
        top_flat_bottom_triangle(tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5], colour);
    }
    else{
        flat_bottom_triangle(tmp[0], tmp[1], tmp[2], tmp[3], x4, y4, colour);
        top_flat_bottom_triangle(tmp[2], tmp[3], x4, y4, tmp[4], tmp[5], colour);
    }
}

void Png::search_and_destroy(color_rgba find_colour, color_rgba change_colour){
    int x1, y1;
    color_rgb rgbcolor = {change_colour.r, change_colour.g, change_colour.b};
    int a = 0, b = 0;
    for(int y = 0; y<h;y++){
        for(int x = 0; x<w; x++){
            bool tmp = false;
            switch(color){
            case PNG_COLOR_TYPE_RGB:
                if(get_pixel_rgb(x, y).r == find_colour.r && get_pixel_rgb(x,y).g == find_colour.g && get_pixel_rgb(x,y).b == find_colour.b){
                    tmp = true;
                }
                break;
            case PNG_COLOR_TYPE_RGBA:
                if(get_pixel_rgba(x, y).r == find_colour.r && get_pixel_rgba(x,y).g == find_colour.g && get_pixel_rgba(x,y).b == find_colour.b){
                    tmp = true;
                }
                break;
            }
            if(tmp){
                int minw = w, w_cur = w;
                int maxh = 0;
                int xt = 0;
                for(int y2 = y; y2 < h; y2++){
                    for(int x2 = x; x2<w; x2++){
                        switch(color){
                        case PNG_COLOR_TYPE_RGB:
                            if(get_pixel_rgb(x2, y2).r != find_colour.r || get_pixel_rgb(x2,y2).g != find_colour.g || get_pixel_rgb(x2,y2).b != find_colour.b){
                                xt = x2;
                                x2 = w+1;
                            }
                            break;
                        case PNG_COLOR_TYPE_RGBA:
                            if(get_pixel_rgba(x2, y2).r != find_colour.r || get_pixel_rgba(x2,y2).g != find_colour.g || get_pixel_rgba(x2,y2).b != find_colour.b){
                                xt = x2;
                                x2 = w+1;
                            }
                            break;
                        }
                        if(x2 == w+1){
                            int w2 = xt-x;
                            if(w2 < w_cur) w_cur = w2;
                            if(w_cur == 0){
                                y2 = h+1;
                                break;
                            }
                            int h2 = y2 - y;
                            if(w2*h2 > minw*maxh){
                                maxh = h2;
                                minw = w_cur;
                            }
                        }
                    }
                }
                if(minw*maxh > a*b){
                    a = minw;
                    b = maxh;
                    x1 = x;
                    y1 = y;
                }
            }
        }
    }
    for(int y = y1; y <= y1+b; y++){
        for(int x = x1; x <= x1+a; x++){
            switch (color) {
            case PNG_COLOR_TYPE_RGB:
                set_pixel_rgb(x, y, rgbcolor);
                break;
            case PNG_COLOR_TYPE_RGBA:
                set_pixel_rgba(x, y, change_colour);
                break;
            }
        }
    }
}

void Png::collage(int N, int M){
    png_bytep new_image = new png_byte[rowb*h*N*M];
    unsigned int bytes_per_pixel = rowb / w;
    for(int y = 0; y < h; y++){
        for(int y1 = 0; y1 < M; y1++){
            for(int x1 = 0; x1 < N; x1++){
                memcpy((new_image + ((y1*h + y)*w*N + x1*w)*bytes_per_pixel), (data.raw + y*w*bytes_per_pixel), rowb);
            }
        }
    }
    delete data.raw;
    data.raw = new_image;
    rowb = rowb*N;
    w = w*N;
    h = h*M;
}

void Png::brightness(double brightness){
    for(unsigned int x = 0; x < w; x++){
        for(unsigned int y = 0; y < h; y++){
            switch(color){
            case PNG_COLOR_TYPE_RGB:{
                color_rgb c = get_pixel_rgb(x, y);
                c.r = std::min(255, (int)(c.r*brightness));
                c.g = std::min(255, (int)(c.g*brightness));
                c.b = std::min(255, (int)(c.b*brightness));
                set_pixel_rgb(x, y, c);
                break;
            }
            case PNG_COLOR_TYPE_RGBA:{
                color_rgba s = get_pixel_rgba(x, y);
                s.r = std::min(255, (int)(s.r*brightness));
                s.g = std::min(255, (int)(s.g*brightness));
                s.b = std::min(255, (int)(s.b*brightness));
                set_pixel_rgba(x, y, s);
                break;
            }
            }
        }
    }
}

void Png::negative(){
    for(unsigned int x = 0; x < w; x++){
        for(unsigned int y = 0; y < h; y++){
            switch(color){
            case PNG_COLOR_TYPE_RGB:{
                color_rgb c = get_pixel_rgb(x, y);
                c.r = 255 - c.r;
                c.g = 255 - c.g;
                c.b = 255 - c.b;
                set_pixel_rgb(x, y, c);
                break;
            }
            case PNG_COLOR_TYPE_RGBA:{
                color_rgba s = get_pixel_rgba(x, y);
                s.r = 255 - s.r;
                s.g = 255 - s.g;
                s.b = 255 - s.b;
                set_pixel_rgba(x, y, s);
                break;
            }
            }
        }
    }
}

void Png::grayscale(){
    for(unsigned int x = 0; x < w; x++){
        for(unsigned int y = 0; y < h; y++){
            switch(color){
            case PNG_COLOR_TYPE_RGB:{
                color_rgb c = get_pixel_rgb(x, y);
                c.r = c.g = c.b = c.r * 0.2126 + c.g * 0.7152 + c.b * 0.722;
                set_pixel_rgb(x, y, c);
                break;
            }
            case PNG_COLOR_TYPE_RGBA:{
                color_rgba s = get_pixel_rgba(x, y);
                s.r = s.g = s.b = s.r * 0.2126 + s.g * 0.7152 + s.b * 0.722;
                set_pixel_rgba(x, y, s);
                break;
            }
            }
        }
    }
}

void Png::save_png(char adress[]){
    FILE* file = fopen(adress, "wb");
    if(!file){
        throw "Не могу открыть файл";
    }

    png_structp png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr){
        throw "Структура не создана";
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr){
        png_destroy_write_struct(&png_ptr, NULL);
        throw "Структура информации о файле не создана";
    }

    if(setjmp(png_jmpbuf(png_ptr))){
        png_destroy_write_struct(&png_ptr, NULL);
        throw "Невозможно инициализировать ввод-вывод";
    }
    png_init_io(png_ptr, file);
    png_set_compression_level(png_ptr, PNG_Z_DEFAULT_COMPRESSION);

    if(setjmp(png_jmpbuf(png_ptr))){
        png_destroy_write_struct(&png_ptr, NULL);
        throw "Невозможно считать чанк IHDR";
    }
    png_set_IHDR(png_ptr, info_ptr, w, h, depth, color, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    if(setjmp(png_jmpbuf(png_ptr))){
        png_destroy_write_struct(&png_ptr, NULL);
        throw "Невозможно записать информацию о файле";
    }
    png_write_info(png_ptr, info_ptr);

    png_bytep* rowb_ptr = new png_bytep[h];
    rowb = png_get_rowbytes(png_ptr, info_ptr);
    for(unsigned int i = 0; i < h; i++)
            rowb_ptr[i] = data.raw + i * rowb;

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_write_struct(&png_ptr, NULL);
        throw "Не получилось записать файл";
    }
    png_write_image(png_ptr, rowb_ptr);

    delete rowb_ptr;
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(file);
}

QImage Png::create_image(){
    QImage::Format format;
    if(color == PNG_COLOR_TYPE_RGB) format = QImage::Format_RGB888;
    else if(color == PNG_COLOR_TYPE_RGBA) format = QImage::Format_RGBA8888;
    else format = QImage::Format_Invalid;

    QImage image(data.raw, w, h, rowb, format);
    return image;
}
