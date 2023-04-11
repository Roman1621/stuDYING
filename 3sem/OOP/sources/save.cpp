#include "../headers/save.h"

std::string Save::get_class_name(){
	return "Save";
}

Byte_array Save::save(){
	Byte_array temp;
	std::string class_name = get_class_name();
	temp.put_object(class_name);
	return temp;
}

void Save::load(Byte_array& temp){
	std::string class_name;
	temp.get_object(class_name);
}