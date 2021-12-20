#include "..//headers/game.h"
#include "game.cpp"
#include "exit_rule.cpp"
#include "death_rule.cpp"

int main(){
    Game<Exit_rule<2>, Death_rule<2>, 2> game;
    game.on_start();
    game.get_win_rule().set_field(game.get_field());
    game.get_win_rule().set_player(game.get_player());
    game.get_win_rule().set_enemy(game.get_enemy());
    game.get_lose_rule().set_player(game.get_player());
    game.update_screen();
    return 0;
}