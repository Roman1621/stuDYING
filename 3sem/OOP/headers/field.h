#ifndef FIELD_H
#define FIELD_H

#include <cstddef>
#include "..//headers/cell.h"
#include "save.h"

class Enemy;

class Field : public Save{
    public:
        Field();
        Field(unsigned int x_weight, unsigned int y_height);
        Field(const Field& other);
        Field(Field&& other);
        Field& operator=(const Field& other);
        Field& operator=(Field&& other);
        ~Field();

        unsigned int get_x() const;
        unsigned int get_y() const;
        Cell& get_cell(unsigned int x, unsigned int y);

        void create_field();
        void create_entrance(unsigned int &entrance_x, unsigned int &entrance_y);
        void create_exit(unsigned int &exit_x, unsigned int &exit_y);
        Cell& put_exit(int distance);

        Cell& create_enemy();
        void put_enemy(std::vector <Enemy*> enemies);
        bool check_enemy(unsigned int x, unsigned int y);

        Cell& create_objects();
        void put_object(std::vector <Object*> objects);
        bool check_object(unsigned int x, unsigned int y);

        virtual std::string get_class_name();
		virtual Byte_array save();
		virtual void load(Byte_array& temp);

    private:
        Cell** field = nullptr;
        unsigned int field_x, field_y;
        unsigned int entrance_x, entrance_y, exit_x, exit_y;
};

#endif