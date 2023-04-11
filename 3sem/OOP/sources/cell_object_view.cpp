#include "..//headers/cell_object_view.h"

Cell_object_view::Cell_object_view(char disp, Cell_objects& holder): disp(disp), holder(holder){}

char Cell_object_view::get_disp() const{
    return disp;
}