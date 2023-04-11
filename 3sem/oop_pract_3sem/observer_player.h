#ifndef OBSERVER_PLAYER_H
#define OBSERVER_PLAYER_H

#include "observer.h"
#include "player.h"

class Obs_Player : public Observer{
    private:
        Player* player;
    
    public:
        using Observer::Observer;
        virtual void set_player(Player& player);
        virtual void notify();
};

#endif
