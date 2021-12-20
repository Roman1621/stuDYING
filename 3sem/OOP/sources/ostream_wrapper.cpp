#include "..//headers/ostream_wrapper.h"

OWrapper::OWrapper(std::ostream& ostr): ostr(ostr), closed(false), link_cnt(0){
    ostr_open();
}

void OWrapper::ostr_open(){}

void OWrapper::ostr_close(){}

OWrapper::~OWrapper(){
    if(!closed)
        ostr_close();
}

void OWrapper::link(){
    if(closed){
        ostr_open();
        closed = false;
    }
    //++link_cnt;
}

void OWrapper::unlink(){
    //--link_cnt;
    if(!closed){
        ostr_close();
        closed = true;
    }
}

void OWrapper::print(const char* message){
    ostr << message << std::endl;
}

void OWrapper::print(const std::string& message){
    ostr << message << std::endl;
}