#ifndef BIND_H
#define BIND_H
#include "player.h"
#include "enemy.h"
#include <map>

class Bind{
    private:
        static std::map<std::string, char> bind;
    
    public:
        static void init_bind();
        static char get_key(std::string key_bind);
};

#endif