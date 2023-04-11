#ifndef ENEMY_H
#define ENEMY_H

#include "..//headers/player.h"

class Field;
class Cell;

class Enemy : public Cell_objects{
    public:
        virtual bool see_player(Player& player) = 0;
        virtual void fighting(Player& player, Field& field) = 0;
        virtual void add_enemy(Cell& holder) = 0;
        virtual void move(Player& player, Field& field) = 0;
        virtual void check_death(Field& field, std::vector <Enemy*>& enemies, int i) = 0;

        virtual unsigned int get_enemy_x() const = 0;
        virtual unsigned int get_enemy_y() const = 0;

        virtual void set_enemy_x(unsigned int enemy_x) = 0;
        virtual void set_enemy_y(unsigned int enemy_y) = 0;
        
        virtual void set_health(unsigned int enemy_health) = 0;
        virtual unsigned int get_health() const = 0;

        friend std::ostream& operator<<(std::ostream& ostr, const Enemy& enemy);
};

std::ostream& operator<<(std::ostream& ostr, const Enemy& enemy);

#endif