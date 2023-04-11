#include "..//headers/object_damage.h"

Object_damage::Object_damage(){
    init();
}

unsigned int Object_damage::get_object_x() const{
    return damage_x;
}

unsigned int Object_damage::get_object_y() const{
    return damage_y;
}

void Object_damage::set_object_x(unsigned int damage_x){
    this->damage_x = damage_x;
}

void Object_damage::set_object_y(unsigned int damage_y){
    this->damage_y = damage_y;
}

void Object_damage::add_object(Cell& holder){
    holder.set_object(*this);
	damage_x = holder.get_cell_x();
	damage_y = holder.get_cell_y();
}

void Object_damage::player_pass(Player& player, Field& field){
    if(get_object_x() == player.get_player_x() && get_object_y() == player.get_player_y()){
		player.set_damage(player.get_damage() + 10);
        field.get_cell(get_object_x(), get_object_y()).del_object();
	}
}

void Object_damage::init(){
    cell_view = new Cell_object_view('d', *this);
}

void Object_damage::check_take(Field& field, std::vector <Object*>& objects, int i){
    if(!field.get_cell(damage_x, damage_y).pres_object())
	{
		objects.erase(objects.begin() + i);
	}
}

std::string Object_damage::get_class_name(){
    return "Object_damage";
}

Byte_array Object_damage::save(){
    Byte_array ba = Object::save();
    ba.put_object(damage_x);
    ba.put_object(damage_y);
    return ba;
}

void Object_damage::load(Byte_array& temp){
    Object::load(temp);
    temp.get_object(damage_x);
    temp.get_object(damage_y);
}