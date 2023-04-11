#include "..//headers/game_rule.h"

void Game_rule::set_player(Player& player){
    this->player = &player;
}

void Game_rule::set_enemy(std::vector<Enemy*>& enemy){
    this->enemy = &enemy;
}

void Game_rule::set_field(Field& field){
    this->field = &field;
}