#ifndef CELL_OBJECT_VIEW_H
#define CELL_OBJECT_VIEW_H

#include <iostream>
#include <vector>

class Cell_objects;

class Cell_object_view{
    public:
        Cell_object_view(char disp, Cell_objects& holder);
        char get_disp() const;

    private:
        char disp;
        Cell_objects& holder;
};

#endif