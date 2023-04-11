#ifndef CLASS_CREATOR_H
#define CLASS_CREATOR_H
#include <map>
#include <functional>
#include <string>
#include "byte_array.h"
#include "save.h"

typedef std::function<void* ()> constructor_lambda;

class Class_creator{
	private:
		static std::map<std::string, constructor_lambda> class_fabrics;
	public:
		static void add_class_fabric(std::string str, constructor_lambda ld);
		static Save* get_object(Byte_array& temp);
		static void init();
};

#endif