#ifndef OSTREAM_WRAPPER_H
#define OSTREAM_WRAPPER_H

#include <fstream>

class OWrapper{
    protected:
        std::ostream& ostr;
        virtual void ostr_open();
        virtual void ostr_close();
    
    private:
        bool closed;
        unsigned link_cnt;
    
    public:
        OWrapper(std::ostream& ostr);
        virtual ~OWrapper();

        void link();
        void unlink();

        virtual void print(const char* message);
        virtual void print(const std::string& message);
};

#endif