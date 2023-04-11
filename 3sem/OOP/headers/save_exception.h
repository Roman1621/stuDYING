#ifndef SAVE_EXCEPTION_H
#define SAVE_EXCEPTION_H

#include <exception>
#include <string>
#include <sstream>

class Buffer_underflow_exception{
    private:
		size_t length; 
		std::string message;
	public:
		Buffer_underflow_exception(size_t len);
		virtual const char* what();
};

class Unknown_classname_exception{
    private:
		std::string class_name; 
		std::string message;
	public:
		Unknown_classname_exception(std::string name);
		virtual const char* what();
};

#endif