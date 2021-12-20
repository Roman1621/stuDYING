#ifndef CELL_OBJECTS_H
#define CELL_OBJECTS_H

#include "..//headers/cell_object_view.h"

class Cell;
class Player;
class Field;

class Cell_objects{
    public:
        virtual void init() = 0;
        virtual Cell_object_view& get();
        virtual ~Cell_objects();
    
    protected:
        Cell_object_view* cell_view;
};

#endif