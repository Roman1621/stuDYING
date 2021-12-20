#ifndef CELL_VIEW_H
#define CELL_VIEW_H

#include <iostream>
#include <vector>

class Cell;

class Cell_view{
    public:
        Cell_view(char disp, Cell& holder);
        char get_disp() const;

    private:
        char disp;
        Cell& holder;
};

#endif