#include "..//headers/death_rule.h"

template <size_t difficulty>
bool Death_rule<difficulty>::done(){
    return player->get_health() == 0 //|| player->get_health() > 100;
    ;
}

template <size_t difficulty>
void Death_rule<difficulty>::set_player(const Player& player){
    this->player = &player;
}