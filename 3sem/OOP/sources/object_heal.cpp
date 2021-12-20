#include "..//headers/object_heal.h"

Object_heal::Object_heal(){
    init();
}

unsigned int Object_heal::get_object_x() const{
    return heal_x;
}

unsigned int Object_heal::get_object_y() const{
    return heal_y;
}

void Object_heal::set_object_x(unsigned int heal_x){
    this->heal_x = heal_x;
}

void Object_heal::set_object_y(unsigned int heal_y){
    this->heal_y = heal_y;
}

void Object_heal::add_object(Cell& holder){
    holder.set_object(*this);
	heal_x = holder.get_cell_x();
	heal_y = holder.get_cell_y();
}

void Object_heal::player_pass(Player& player, Field& field){
    if(get_object_x() == player.get_player_x() && get_object_y() == player.get_player_y())
	{
		player.set_health(100);
		field.get_cell(get_object_x(), get_object_y()).del_object();
	}
}

void Object_heal::init(){
    cell_view = new Cell_object_view('H', *this);
}

Object_heal::~Object_heal(){
    if(cell_view)
        delete cell_view;
}

void Object_heal::check_take(Field& field, std::vector <Object*>& objects, int i){
    if(!field.get_cell(get_object_x(), get_object_y()).pres_object())
	{
		objects.erase(objects.begin() + i);
	}
}