#ifndef OBJECT_H
#define OBJECT_H

#include "..//headers/cell_objects.h"

class Object : public Cell_objects{
    public:
        virtual void add_object(Cell& holder) = 0;
        virtual void player_pass(Player& player, Field& field) = 0;
        virtual void check_take(Field& field, std::vector <Object*>& objects, int i) = 0;

        virtual unsigned int get_object_x() const = 0;
        virtual unsigned int get_object_y() const = 0;

        virtual void set_object_x(unsigned int object_x) = 0;
        virtual void set_object_y(unsigned int object_y) = 0;
};

#endif