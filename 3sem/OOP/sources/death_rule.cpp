#include "../headers/death_rule.h"

bool Death_rule::done(){
    return player->get_health() <= 0;
}