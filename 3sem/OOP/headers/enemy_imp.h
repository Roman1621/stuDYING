#ifndef ENEMY_IMP_H
#define ENEMY_IMP_H

#include "..//headers/enemy.h"

class Enemy_imp : public Enemy{
    private:
        unsigned int health = 100, damage = 10;
        unsigned int imp_x = 0, imp_y = 0;
        
    public:
        Enemy_imp();
        
        virtual bool see_player(Player& player);
        virtual void fighting(Player& player, Field& field);
        virtual void add_enemy(Cell& holder);
        virtual void move(Player& player, Field& field);

        virtual void check_death(Field& field, std::vector <Enemy*>& enemies, int i);
        
        unsigned int get_enemy_x() const;
        unsigned int get_enemy_y() const;

        void set_enemy_x(unsigned int imp_x);
        void set_enemy_y(unsigned int imp_y);

        unsigned int get_health() const;
        void set_health(unsigned int health_sp);
        
        virtual void init();

        virtual std::string get_class_name();
		virtual Byte_array save();
		virtual void load(Byte_array& temp);
};

#endif