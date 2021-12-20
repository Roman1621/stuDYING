#include "..//headers/field_view.h"

Field_view::Field_view(Field& view_f) : view(view_f) {}

void Field_view::display(){
    for(int i = 0; i < view.get_y(); i++){
        for(int j = 0; j < view.get_x(); j++){
            std::cout << view.get_cell(j,i).get_display().get_disp();
        }
    std::cout << std::endl;
    }
}
