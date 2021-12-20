#include "..//headers/cell_objects.h"

Cell_object_view& Cell_objects::get(){
    return *cell_view;
}

Cell_objects::~Cell_objects(){
    delete cell_view;
}