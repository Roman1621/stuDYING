#ifndef OBJECT_DAMAGE_H
#define OBJECT_DAMAGE_H

#include "..//headers/object.h"
#include "..//headers/cell.h"
#include "..//headers/field.h"

class Object_damage : public Object{
    private:
        unsigned int damage_x = 0, damage_y = 0;
    
    public:
        Object_damage();
        
		virtual void add_object(Cell& holder);
		virtual void player_pass(Player& player, Field& field);	
		void init();
		virtual void check_take(Field& field, std::vector <Object*>& objects, int i);

        unsigned int get_object_x() const;
        unsigned int get_object_y() const;

        void set_object_x(unsigned int damage_x);
        void set_object_y(unsigned int damage_y);
        
        virtual std::string get_class_name();
		virtual Byte_array save();
		virtual void load(Byte_array& temp);
};

#endif