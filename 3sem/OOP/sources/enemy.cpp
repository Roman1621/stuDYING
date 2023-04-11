#include "..//headers/enemy.h"

std::ostream& operator<<(std::ostream& ostr, const Enemy& enemy){
    ostr  << " health: " << enemy.get_health()
        << " Pos_Enemy_X: " << enemy.get_enemy_x()
        << " Pos_Enemy_Y: " << enemy.get_enemy_y();
    return ostr;
}