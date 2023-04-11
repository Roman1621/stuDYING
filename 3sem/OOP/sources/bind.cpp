#include "..//headers/bind.h"

std::map<std::string, char> Bind::bind;

void Bind::init_bind(){
        bind = {
                {"Exit", 'q'},
                {"Up", 'w'},
                {"Right", 'd'},
                {"Down", 's'},
                {"Left", 'a'},
                {"Fighting", 'f'},
                {"Save", 'c'},
                {"Load", 'x'}
        };
}

char Bind::get_key(std::string key_bind){
        auto key = bind.find(key_bind);
        if(key == bind.end()){
                return '\0';
        }
        return key->second;
}