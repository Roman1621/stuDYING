#ifndef DEATH_RULE_H
#define DEATH_RULE_H

#include "game_rule.h"


class Death_rule : public Game_rule{
    public:
        virtual bool done();
};

#endif