#ifndef EXIT_RULE_H
#define EXIT_RULE_H

#include "game_rule.h"
#include "player.h"
#include "field.h"

template <size_t difficulty>
class Exit_rule : public Game_rule<difficulty>{
    public:
        virtual bool done();
        void set_player(Player& player);
        void set_enemy(std::vector <Enemy*>& enemy);
        void set_field(Field& field);
    
    private:
        const Player* player;
        const std::vector<Enemy*>* enemy;
        Field* field;
};

#endif