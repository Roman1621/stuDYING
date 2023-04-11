#ifndef SAVE_H
#define SAVE_H
#include "byte_array.h"
#include <string>

class Save{
    public:
        virtual std::string get_class_name();
		virtual Byte_array save();
		virtual void load(Byte_array& temp);
};

#endif