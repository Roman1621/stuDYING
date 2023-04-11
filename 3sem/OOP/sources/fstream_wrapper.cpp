#include "..//headers/fstream_wrapper.h"

FWrapper::FWrapper(std::ofstream& ostr, const char* file_name) : OWrapper((std::ostream&)ostr){
    this->file_name = file_name;
    ostr_open();
}

void FWrapper::ostr_open(){
    ((std::ofstream&)ostr).open(file_name);
}

void FWrapper::ostr_close(){
    ((std::ofstream&)ostr).close();
}