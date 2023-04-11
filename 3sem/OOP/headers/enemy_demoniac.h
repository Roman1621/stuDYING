#ifndef ENEMY_DEMONIAC_H
#define ENEMY_DEMONIAC_H

#include "..//headers/enemy.h"

class Enemy_demoniac : public Enemy{
    private:
        unsigned int health = 50, damage = 5;
        unsigned int demoniac_x = 0, demoniac_y = 0;
        int count_move = 0;
        enum dir_of_move{
            Up = 0, Right, Down, Left
        };
        dir_of_move dir = Up;
    
    public:
        Enemy_demoniac();
        
        virtual bool see_player(Player& player);
        virtual void fighting(Player& player, Field& field);
        virtual void add_enemy(Cell& holder);
        
        virtual void move(Player& player, Field& field);
        void move_up(Player& player, Field& field);
        void move_right(Player& player, Field& field);
        void move_down(Player& player, Field& field);
        void move_left(Player& player, Field& field);

        virtual void check_death(Field& field, std::vector <Enemy*>& enemies, int i);
        
        unsigned int get_enemy_x() const;
        unsigned int get_enemy_y() const;

        void set_enemy_x(unsigned int demoniac_x);
        void set_enemy_y(unsigned int demoniac_y);

        unsigned int get_health() const;
        void set_health(unsigned int health_sp);
        
        virtual void init();
        
        virtual std::string get_class_name();
		virtual Byte_array save();
		virtual void load(Byte_array& temp);
};

#endif