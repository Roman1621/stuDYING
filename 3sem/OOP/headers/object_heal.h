#ifndef OBJECT_HEAL_H
#define OBJECT_HEAL_H

#include "..//headers/object.h"
#include "..//headers/cell.h"
#include "..//headers/field.h"

class Object_heal : public Object{
    private:
        unsigned int heal_x = 0, heal_y = 0;
    
    public:
        Object_heal();
        ~Object_heal();
        
		virtual void add_object(Cell& holder);
		virtual void player_pass(Player& player, Field& field);	
		void init();
		virtual void check_take(Field& field, std::vector <Object*>& objects, int i);

        unsigned int get_object_x() const;
        unsigned int get_object_y() const;

        void set_object_x(unsigned int heal_x);
        void set_object_y(unsigned int heal_y);
};

#endif