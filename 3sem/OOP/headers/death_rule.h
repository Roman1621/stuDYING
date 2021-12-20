#ifndef DEATH_RULE_H
#define DEATH_RULE_H

#include "game_rule.h"
#include "player.h"

template <size_t difficulty>
class Death_rule : public Game_rule<difficulty>{
    const Player* player;

    public:
        void set_player(const Player& player);
        virtual bool done();
};

#endif