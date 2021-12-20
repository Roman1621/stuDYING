#ifndef GAME_RULE_H
#define GAME_RULE_H
#include <cstddef>

template <size_t difficulty>
class Game_rule{
    public:
        virtual bool done() = 0;
};

#endif