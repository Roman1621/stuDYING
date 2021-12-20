#ifndef OBJECT_TRAP_H
#define OBJECT_TRAP_H

#include "..//headers/object.h"
#include "..//headers/cell.h"
#include "..//headers/field.h"

class Object_trap : public Object{
    private:
        unsigned int trap_x = 0, trap_y = 0;
    
    public:
        Object_trap();
        ~Object_trap();
        
		virtual void add_object(Cell& holder);
		virtual void player_pass(Player& player, Field& field);	
		void init();
		virtual void check_take(Field& field, std::vector <Object*>& objects, int i);

        unsigned int get_object_x() const;
        unsigned int get_object_y() const;

        void set_object_x(unsigned int trap_x);
        void set_object_y(unsigned int trap_y);
};

#endif