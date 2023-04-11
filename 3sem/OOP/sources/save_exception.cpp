#include "..//headers/save_exception.h"

Buffer_underflow_exception::Buffer_underflow_exception(size_t len):length(len){
	std::stringstream buf;
	buf << "Buffer underflow of size " << length;
	message = buf.str();
}

const char* Buffer_underflow_exception::what(){
	return message.c_str();
}

Unknown_classname_exception::Unknown_classname_exception(std::string name) : class_name(name){
	std::stringstream buf;
	buf << "Unknown class name " << class_name;
	message = buf.str();
}

const char* Unknown_classname_exception::what(){
	return message.c_str();
}