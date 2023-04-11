#include "..//headers/observer_enemy.h"

#include <sstream>

void Obs_Enemy::set_enemy(Enemy& enemy){
    this->enemy = &enemy;
    enemy.set_observer(*this);
}

void Obs_Enemy::notify(){
    Enemy& en = *enemy;
    for(auto i = ostr_list.begin(); i != ostr_list.end(); i++){
        OWrapper& owrapper = (*i);
        std::stringstream string_stream;
        string_stream << en;
        owrapper.print(string_stream.str());
    }
}