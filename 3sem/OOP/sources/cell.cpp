#include "..//headers/cell.h"

Cell::Cell(){
    cell_view = new Cell_view('*', *this);
}

Cell::~Cell(){
    if(cell_view){
        delete cell_view;
    }
}

Cell& Cell::operator=(const Cell& other){
    pass = other.pass;
    exit = other.exit;
    entrance = other.entrance;
    display = other.display;
    cell_x = other.cell_x;
    cell_y = other.cell_y;
    object_on_cell  =other.object_on_cell;
    enemy_on_cell = other. enemy_on_cell;
    player_on_cell = other.player_on_cell;
    return *this;
}

unsigned int Cell::get_cell_x() const{
    return cell_x;
}

unsigned int Cell::get_cell_y() const{
    return cell_y;
}

void Cell::set_cell_x(unsigned int x){
    cell_x = x;
}

void Cell::set_cell_y(unsigned int y){
    cell_y = y;
}

void Cell::set_display(char disp){
    display = disp;
}

Cell_view& Cell::get_display(){
    return *cell_view;
}

void Cell::set_entrance(bool b){
    entrance = b;
}

bool Cell::get_entrance(){
    return entrance;
}

void Cell::set_exit(bool b){
    exit = b;
}

bool Cell::get_exit(){
    return exit;
}

void Cell::set_pass(bool b){
    pass = b;
}

bool Cell::get_pass(){
    return pass;
}

void Cell::set_object(Cell_objects& object){
    object_on_cell = &object;
}

Cell_objects& Cell::get_object(){
    return *object_on_cell;
}

void Cell::del_object(){
    object_on_cell = nullptr;
}

bool Cell::pres_object(){
    return object_on_cell;
}

void Cell::set_enemy(Cell_objects& enemy){
    enemy_on_cell = &enemy;
}

Cell_objects& Cell::get_enemy(){
    return *enemy_on_cell;
}

void Cell::del_enemy(){
    enemy_on_cell = nullptr;
}

bool Cell::pres_enemy(){
    return enemy_on_cell;
}

void Cell::set_player(Cell_objects& player){
    player_on_cell = &player;
}

Cell_objects& Cell::get_player(){
    return *player_on_cell;
}

void Cell::del_player(){
    player_on_cell = nullptr;
}

bool Cell::pres_player(){
    return player_on_cell;
}

std::string Cell::get_class_name(){
    return "Cell";
}

Byte_array Cell::save(){
    Byte_array ba = Save::save();
    ba.put_object(pass);
    ba.put_object(entrance);
    ba.put_object(exit);
    ba.put_object(display);
    ba.put_object(cell_x);
    ba.put_object(cell_y);
    bool has_object = pres_object(), has_enemy = pres_enemy(), has_player = pres_player();
    ba.put_object(has_object);
    ba.put_object(has_enemy);
    ba.put_object(has_player);
    if(has_object){
        Byte_array o = object_on_cell->save();
        ba += o;
    }

    if(has_enemy){
        Byte_array o = enemy_on_cell->save();
        ba += o;
    }
    
    if(has_player){
        Byte_array o = player_on_cell->save();
        ba += o;
    }

    return ba;
}

void Cell::load(Byte_array& temp){
    Save::load(temp);
    temp.get_object(pass);
    temp.get_object(entrance);
    temp.get_object(exit);
    temp.get_object(display);
    temp.get_object(cell_x);
    temp.get_object(cell_y);
    bool has_object, has_enemy, has_player;
    temp.get_object(has_object);
    temp.get_object(has_enemy);
    temp.get_object(has_player);
    if(has_object){
        object_on_cell = (Cell_objects*) Class_creator::get_object(temp);
    }
    else{
        object_on_cell = nullptr;
    }

    if(has_enemy){
        enemy_on_cell = (Cell_objects*) Class_creator::get_object(temp);
    }
    else{
        enemy_on_cell = nullptr;
    }

    if(has_player){
        player_on_cell = (Cell_objects*) Class_creator::get_object(temp);
    }
    else{
        player_on_cell = nullptr;
    }
}