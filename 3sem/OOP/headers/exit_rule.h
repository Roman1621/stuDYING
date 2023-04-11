#ifndef EXIT_RULE_H
#define EXIT_RULE_H

#include "game_rule.h"


class Exit_rule : public Game_rule{
    public:
        virtual bool done();
};

#endif