#ifndef PLAYER_H
#define PLAYER_H

#include "..//headers/cell_objects.h"
class Field;
class Enemy;

class Player : public Cell_objects{
    private:
        unsigned int health = 100;
        unsigned int damage = 20;
        unsigned int player_x = 0, player_y = 0;
    
    public:
        Player();
        //~Player();

        unsigned int get_player_x() const;
        unsigned int get_player_y() const;
        void set_player_x(unsigned int player_x);
        void set_player_y(unsigned int player_y);

        unsigned int get_health() const;
        void set_health(unsigned int health);

        unsigned int get_damage() const;
        void set_damage(unsigned int damage);

        bool check_death(Field& field);

        void move_up(Field& field);
        void move_right(Field& field);
        void move_down(Field& field);
        void move_left(Field& field);
        
        bool see_enemy(Enemy* enemy, Field field);
        void fighting(Field& field);

        virtual void init();

        friend std::ostream& operator<<(std::ostream& ostr, const Player& player);
};

std::ostream& operator<<(std::ostream& ostr, const Player& player);

#endif