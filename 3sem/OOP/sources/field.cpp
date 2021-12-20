#include "..//headers/field.h"
#include <math.h>
#include <random>
#include <tuple>

Field::Field(unsigned int x_weight, unsigned int y_height){
    this->field_x = x_weight + 2;
    this->field_y = y_height + 2;
    create_field();
}

Field::Field(const Field& other){
    field_x = other.field_x;
    field_y = other.field_y;

    field = new Cell* [field_y];
    for(unsigned int i = 0; i < field_y; i++){
        field[i] = new Cell [field_x];
        std::copy(other.field[i], other.field[i]+field_x, field[i]);
    }
}

Field::Field(Field&& other){
    std::swap(field_x, other.field_x);
    std::swap(field_y, other.field_y);
    std::swap(field, other.field);
}

Field& Field::operator=(const Field& other){
    if(this == &other)
        return *this;
  
    field_x = other.get_x();
    field_y = other.get_y();
    for(unsigned int i = 0; i < field_y; i++)
	    delete[] field[i];
    delete[] field;

    field = new Cell* [field_y];
    for(unsigned int i = 0; i < field_y; i++){
        field[i] = new Cell [field_x];
        std::copy(other.field[i], other.field[i]+field_x, field[i]);
    }

    return *this;
}

Field& Field::operator=(Field&& other){
    if(this == &other)
        return *this;
    
    std::swap(field_x, other.field_x);
    std::swap(field_y, other.field_y);
    std::swap(field, other.field);

    return *this;
}

Field::~Field(){
    if(field){
	for(unsigned int i = 0; i < field_y; i++){
        	delete[] field[i];
    	}
    	delete[] field;
    }
}

unsigned int Field::get_x() const{
    return field_x;
}

unsigned int Field::get_y() const{
    return field_y;
}

Cell& Field::get_cell(unsigned int x, unsigned int y){
	if(x > field_x || y > field_y)
        throw "Координаты за пределами досигаемости";

    return field[y][x];
}

void Field::create_field(){
    field = new Cell* [field_y];
    for(unsigned int i = 0; i<field_y; i++){
        field[i] = new Cell [field_x];
        for(unsigned int j = 0; j < field_x; j++){
            field[i][j].set_cell_x(j);
            field[i][j].set_cell_y(i);
            if(i == 0 || i == field_y-1){
                field[i][j].set_pass(0);
                field[i][j].set_display('W');
            }
            else{
                field[i][0].set_pass(0);
                field[i][0].set_display('W');
                field[i][field_x-1].set_pass(0);
                field[i][field_x-1].set_display('W');
            }
        }
    }
}

void Field::create_entrance(unsigned int &entrance_x, unsigned int &entrance_y){
    std::mt19937 generator;
    std::random_device random_gen;
    generator.seed(random_gen());
    std::uniform_int_distribution<> dist_side(0, 3);
    std::uniform_int_distribution<> rand_num(0,1);

    unsigned int side = dist_side(generator);
    if(side == 0 || side == 2)
    {
        std::uniform_int_distribution<> dist_y(1, field_y-2);
        entrance_y = dist_y(generator);
        if(rand_num(generator))
            entrance_x = 0;
        else
            entrance_x = field_x-1;
    }
    else
    {
        if(rand_num(generator))
            entrance_y = field_y-1;
        else
            entrance_y = 0;
        std::uniform_int_distribution<> dist_x(1, field_x-2);
        entrance_x = dist_x(generator);
    }
}

void Field::create_exit(unsigned int &exit_x, unsigned int &exit_y){
	std::mt19937 generator;
    std::random_device random_gen;
    generator.seed(random_gen());
    std::uniform_int_distribution<> dist_side(0, 3);
    std::uniform_int_distribution<> rand_num(0,1);

    unsigned int side = dist_side(generator);
    if(side == 0 || side == 2)
    {
        std::uniform_int_distribution<> dist_y(1, field_y-2);
        exit_y = dist_y(generator);
        if(rand_num(generator))
            exit_x = 0;
        else
            exit_x = field_x-1;
    }
    else
    {
        if(rand_num(generator))
            exit_y = field_y-1;
        else
            exit_y = 0;

        std::uniform_int_distribution<> dist_x(1, field_x-2);
        exit_x = dist_x(generator);
    }
}

Cell& Field::put_exit(int distance){
    unsigned int entrance_x = 0, entrance_y = 0, exit_x = 0, exit_y = 0;

    do
    {
        create_entrance(entrance_x, entrance_y);
        create_exit(exit_x, exit_y);
    } while((((exit_x-entrance_x) <= distance) || ((exit_x-entrance_x) >= (-1)*distance)) || 
            (((exit_y-entrance_y) <= distance) || ((exit_y-entrance_y) >= (-1)*distance)));

    field[exit_y][exit_x].set_display('O');
    field[exit_y][exit_x].set_exit(true);
    field[exit_y][exit_x].set_pass(true);
    field[entrance_y][entrance_x].set_display('E');
    field[entrance_y][entrance_x].set_entrance(true);
    field[entrance_y][entrance_x].set_pass(true);
    return field[entrance_y][entrance_x];
}

Cell& Field::create_enemy(){
    std::mt19937 generator;
    std::random_device rand;
    generator.seed(rand());
    std::uniform_int_distribution<> enemy_x(1, field_x-2);
    std::uniform_int_distribution<> enemy_y(1, field_y-2);
    unsigned int copy_x = 0, copy_y = 0, i = 0;
    do{
        copy_x = enemy_x(generator);
        copy_y = enemy_y(generator);
        i++;
    }while(check_enemy(copy_x, copy_y));

    return field[copy_y][copy_x];
}

void Field::put_enemy(std::vector <Enemy*> enemies){
    for(int i = 0; i < enemies.size(); i++){
        enemies.at(i)->add_enemy(create_enemy());
    }
}

bool Field::check_enemy(unsigned int x, unsigned int y){
    return (field[y][x].pres_enemy() || field[y][x].pres_object()
    || field[y][x].pres_player() || !field[y][x].get_pass() 
    || (((entrance_x-field[y][x].get_cell_x()) < 2) && ((entrance_x-field[y][x].get_cell_x()) > 2)) 
    || (((entrance_y-field[y][x].get_cell_y())<2) && ((entrance_y-field[y][x].get_cell_x()) > 2))
    || field[y+1][x].pres_enemy() || field[y-1][x].pres_enemy() 
    || field[y][x+1].pres_enemy() || field[y][x-1].pres_enemy() 
    || field[y+1][x+1].pres_enemy() || field[y+1][x-1].pres_enemy()
    || field[y-1][x+1].pres_enemy() || field[y-1][x-1].pres_enemy());
}

Cell& Field::create_objects(){
    std::mt19937 generator;
    std::random_device rand;
    generator.seed(rand());
    std::uniform_int_distribution<> object_x(1, field_x-2);
    std::uniform_int_distribution<> object_y(1, field_y-2);
    unsigned int copy_x = 0, copy_y = 0, i = 0;
    do{
        copy_x = object_x(generator);
        copy_y = object_y(generator);
        i++;
    }while(check_object(copy_x, copy_y));

    return field[copy_y][copy_x];
}

void Field::put_object(std::vector <Object*> objects){
    for(int i = 0; i < objects.size(); i++){
        objects.at(i)->add_object(create_objects());
    }
}

bool Field::check_object(unsigned int x, unsigned int y){
    return (field[y][x].pres_enemy() || field[y][x].pres_object() 
    || field[y][x].pres_player() || !field[y][x].get_pass()
    || field[y+1][x].pres_enemy() || field[y][x+1].pres_enemy() 
    || field[y][x-1].pres_enemy() || field[y+1][x+1].pres_enemy()
    || field[y-1][x].pres_enemy() || field[y+1][x-1].pres_enemy()
    || field[y-1][x+1].pres_enemy() || field[y-1][x-1].pres_enemy());
}