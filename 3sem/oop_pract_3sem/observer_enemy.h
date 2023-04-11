#ifndef OBSERVER_ENEMY_H
#define OBSERVER_ENEMY_H

#include "observer.h"
#include "enemy.h"

class Obs_Enemy : public Observer{
    private:
        Enemy* enemy;
    
    public:
        using Observer::Observer;
        virtual void set_enemy(Enemy& enemy);
        virtual void notify();
};

#endif