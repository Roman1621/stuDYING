#ifndef BYTE_ARRAY_H
#define BYTE_ARRAY_H

#include <sstream>
#include <cstddef>
#include <string>
#include "save_exception.h"
#include <fstream>

class Byte_array : std::stringstream{
    public:
        Byte_array(const Byte_array& other){
			str(other.str());
		}

		Byte_array() {}

		template<class T>
		void put_object(T& object){
			write((const char*)&object, sizeof(object));
		}

		template<class T>
		void get_object(T& object){
			read((char*)&object, sizeof(object));
			if(!good())
				throw Buffer_underflow_exception(sizeof(object));
			
		}

		void put_object(std::string& object){
			write((const char*)object.c_str(), object.length()+1);
		}

		void get_object(std::string& object){
			std::stringstream buf;
			int c;
			while((c = get()) != '\0')
			{
				if(!str().length())
					throw Buffer_underflow_exception(1); 
				buf << (char)c;
			}
			object = buf.str();
		}

		void back_pointer(int offset){
			seekg(-offset, std::ios_base::cur);
		}

		Byte_array& operator += (Byte_array& bs2){
			size_t sz = bs2.str().length();
			unsigned char* buf = new unsigned char [sz];
			bs2.read((char*)buf, sz);
			write((const char*)buf, sz);
			delete buf;
			return *this;
		}

		void write_out(std::fstream& stream){
			seekg(0, std::ios_base::beg);
			size_t sz = str().length();
			unsigned char* buf = new unsigned char [sz];
			read((char*)buf, sz);
			stream.write((const char*)buf, sz);
			delete buf;
		}

		void read_in(std::fstream& stream){
			stream.seekg(0, std::ios_base::end);
			size_t file_size = stream.tellg();
			stream.seekg(0);
			unsigned char* buf = new unsigned char [file_size];
			stream.read((char*)buf, file_size);
			write((const char*)buf, file_size);
			delete buf;
			seekg(0, std::ios_base::beg);
		}
};

#endif