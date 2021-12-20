#include "..//headers/cell_view.h"
#include "..//headers/cell.h"

Cell_view::Cell_view(char disp, Cell& holder): disp(disp), holder(holder){}

char Cell_view::get_disp() const{
    if(holder.pres_player()) return holder.get_player().get().get_disp();
    if(holder.pres_enemy()) return holder.get_enemy().get().get_disp();
    if(holder.pres_object()) return holder.get_object().get().get_disp();
    if(holder.get_entrance()) return 'O';
    if(holder.get_exit()) return 'E';
    if(!holder.get_pass()) return '0';
    return disp;
}