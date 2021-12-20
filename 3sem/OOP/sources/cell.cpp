#include "..//headers/cell.h"

Cell::Cell(){
    cell_view = new Cell_view('*', *this);
}

Cell::~Cell(){
    if(cell_view){
        delete cell_view;
    }
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