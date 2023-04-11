#include "..//headers/object_trap.h"

Object_trap::Object_trap(){
    init();
}


unsigned int Object_trap::get_object_x() const{
    return trap_x;
}

unsigned int Object_trap::get_object_y() const{
    return trap_y;
}

void Object_trap::set_object_x(unsigned int trap_x){
    this->trap_x = trap_x;
}

void Object_trap::set_object_y(unsigned int trap_y){
    this->trap_y = trap_y;
}

void Object_trap::add_object(Cell& holder){
    holder.set_object(*this);
	trap_x = holder.get_cell_x();
	trap_y = holder.get_cell_y();
}

void Object_trap::player_pass(Player& player, Field& field){
    if(get_object_x() == player.get_player_x() && get_object_y() == player.get_player_y()){
		player.set_health(player.get_health() - 10);
        if(player.get_health() <= 0){
            field.get_cell(get_object_x(), get_object_y()).del_player();
            field.get_cell(get_object_x(), get_object_y()).set_pass(true);
        }
        field.get_cell(get_object_x(), get_object_y()).del_object();
	}
}

void Object_trap::init(){
    cell_view = new Cell_object_view('T', *this);
}

void Object_trap::check_take(Field& field, std::vector <Object*>& objects, int i){
    if(!field.get_cell(get_object_x(), get_object_y()).pres_object())
	{
		objects.erase(objects.begin() + i);
	}
}

std::string Object_trap::get_class_name(){
    return "Object_trap";
}

Byte_array Object_trap::save(){
    Byte_array ba = Object::save();
    ba.put_object(trap_x);
    ba.put_object(trap_y);
    return ba;
}

void Object_trap::load(Byte_array& temp){
    Object::load(temp);
    temp.get_object(trap_x);
    temp.get_object(trap_y);
}