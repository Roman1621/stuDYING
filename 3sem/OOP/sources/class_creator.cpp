#include "../headers/class_creator.h"
#include "../headers/enemy_demoniac.h"
#include "../headers/enemy_imp.h"
#include "../headers/enemy_knight.h"
#include "../headers/object_damage.h"
#include "../headers/object_heal.h"
#include "../headers/object_trap.h"
#include "../headers/cell.h"
#include "../headers/field.h"
#include "../headers/player.h"

std::map<std::string, constructor_lambda> Class_creator::class_fabrics;

void Class_creator::add_class_fabric(std::string str, constructor_lambda fab){
	class_fabrics[str] = fab;
}

Save* Class_creator::get_object(Byte_array& temp){
	std::string class_name;
	temp.get_object(class_name);
	int back_w = class_name.length()+1;
	temp.back_pointer(back_w);
	auto ftemp = class_fabrics.find(class_name);
	if(ftemp == class_fabrics.end())
		throw Unknown_classname_exception(class_name);
	Save* object = (Save*)(ftemp->second());
	object->load(temp);
	return object;
}

void Class_creator::init(){
	add_class_fabric("Field", [](){return new Field;});
	add_class_fabric("Cell", [](){return new Cell;});
	add_class_fabric("Enemy_demoniac", [](){return new Enemy_demoniac;});
	add_class_fabric("Enemy_imp", [](){return new Enemy_imp;});
	add_class_fabric("Enemy_knight", [](){return new Enemy_knight;});
	add_class_fabric("Object_damage", [](){return new Object_damage;});
	add_class_fabric("Object_heal", [](){return new Object_heal;});
	add_class_fabric("Object_trap", [](){return new Object_trap;});
	add_class_fabric("Player", [](){return new Player;});
}