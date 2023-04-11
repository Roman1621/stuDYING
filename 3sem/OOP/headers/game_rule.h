#ifndef GAME_RULE_H
#define GAME_RULE_H
#include <cstddef>
#include "player.h"
#include "enemy.h"
#include "field.h"


class Game_rule{
    protected:
        Player* player;
        std::vector<Enemy*>* enemy;
        Field* field;
    
    public:
        virtual bool done() = 0;
        void set_player(Player& player);
        void set_enemy(std::vector <Enemy*>& enemy);
        void set_field(Field& field);
};

#endif