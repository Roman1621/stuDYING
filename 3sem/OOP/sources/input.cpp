#include "..//headers/input.h"
#include <termios.h>
#include <unistd.h>
#include <cstdio>

static void clear_terminal_icanon(){
    static struct termios t_old, t_new;
    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
}

static void set_terminal_icanon(){
    static struct termios t_old, t_new;
    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
}

Input::Input(){
    clear_terminal_icanon();
}

Input::~Input(){
    set_terminal_icanon();
}

char Input::get_input(){
    return getchar();
}