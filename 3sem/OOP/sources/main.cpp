#include "..//headers/game.h"
#include "game.cpp"

int main(){
    Class_creator::init();
    Game<Exit_rule, Death_rule, 2> game;
    Bind::init_bind();
    game.on_start();
    game.get_win_rule().set_field(game.get_field());
    game.get_win_rule().set_player(game.get_player());
    game.get_win_rule().set_enemy(game.get_enemy());
    game.get_lose_rule().set_player(game.get_player());
    game.update_screen();
    return 0;
}