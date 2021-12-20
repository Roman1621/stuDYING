#include "..//headers/exit_rule.h"

template <size_t difficulty>
bool Exit_rule<difficulty>::done(){
    return player && field->get_cell(player->get_player_x(), player->get_player_y()).get_exit();
}

template <size_t difficulty>
void Exit_rule<difficulty>::set_player(Player& player){
    this->player = &player;
}

template <size_t difficulty>
void Exit_rule<difficulty>::set_enemy(std::vector<Enemy*>& enemy){
    this->enemy = &enemy;
}

template <size_t difficulty>
void Exit_rule<difficulty>::set_field(Field& field){
    this->field = &field;
}