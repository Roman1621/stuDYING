#include "..//headers/observer_player.h"

#include <sstream>

void Obs_Player::set_player(Player& player){
    this->player = &player;
    player.set_observer(*this);
}

void Obs_Player::notify(){
    Player& pl = *player;
    for(auto i = ostr_list.begin(); i != ostr_list.end(); i++){
        OWrapper& owrapper = (*i);
        std::stringstream string_stream;
        string_stream << pl;
        owrapper.print(string_stream.str());
    }
}
