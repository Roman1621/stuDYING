#ifndef FSTREAM_WRAPPER_H
#define FSTREAM_WRAPPER_H

#include "ostream_wrapper.h"

class FWrapper: public OWrapper{
    protected:
        virtual void ostr_open();
        virtual void ostr_close();
    
    private:
        const char* file_name;
    
    public:
        FWrapper(std::ofstream& ostr, const char* file_name);
};

#endif