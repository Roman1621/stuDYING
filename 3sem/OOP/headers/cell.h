#ifndef CELL_H
#define CELL_H

#include "..//headers/enemy.h"
#include "..//headers/player.h"
#include "..//headers/cell_view.h"
#include "..//headers/object.h"

class Cell{
    private:
        Cell_objects* object_on_cell = nullptr;
        Cell_objects* enemy_on_cell = nullptr;
        Cell_objects* player_on_cell = nullptr;
        Cell_view* cell_view;
        bool pass = 1;
        bool entrance = 0;
        bool exit = 0;
        char display = '*';
        unsigned int cell_x = 0, cell_y = 0;

    public:
        Cell();
        ~Cell();

        unsigned int get_cell_x() const;
        unsigned int get_cell_y() const;
        void set_cell_x(unsigned int x);
        void set_cell_y(unsigned int y);

        void set_display(char disp);
        Cell_view& get_display();

        void set_entrance(bool b);
        bool get_entrance();

        void set_exit(bool b);
        bool get_exit();

        void set_pass(bool b);
        bool get_pass();

        Cell_objects& get_object();
        void set_object(Cell_objects& object);
        bool pres_object();
        void del_object();

        Cell_objects& get_enemy();
        void set_enemy(Cell_objects& enemy);
        bool pres_enemy();
        void del_enemy();

        Cell_objects& get_player();
        void set_player(Cell_objects& player);
        bool pres_player();
        void del_player();
};

#endif
