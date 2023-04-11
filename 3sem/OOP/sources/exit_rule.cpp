#include "..//headers/exit_rule.h"

bool Exit_rule::done(){
    return player && field->get_cell(player->get_player_x(), player->get_player_y()).get_exit();
}