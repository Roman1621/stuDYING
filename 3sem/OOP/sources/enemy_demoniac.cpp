#include "..//headers/enemy_demoniac.h"
#include "..//headers/field.h"
#include "..//headers/logger.h"
#include <cstdlib>
#include <random>
#include <tuple>
#include <sstream>

Enemy_demoniac::Enemy_demoniac(){
    init();
}

void Enemy_demoniac::init(){
    cell_view = new Cell_object_view('D', *this);
}

unsigned int Enemy_demoniac::get_enemy_x() const{
    return demoniac_x;
}

unsigned int Enemy_demoniac::get_enemy_y() const{
    return demoniac_y;
}

void Enemy_demoniac::set_enemy_x(unsigned int demoniac_x){
    this->demoniac_x = demoniac_x;
}

void Enemy_demoniac::set_enemy_y(unsigned int demoniac_y){
    this->demoniac_y = demoniac_y;
}

unsigned int Enemy_demoniac::get_health() const{
    return health;
}

void Enemy_demoniac::set_health(unsigned int health_sp){
    health = health_sp;
}

bool Enemy_demoniac::see_player(Player& player){
    unsigned abs_x = std::max(player.get_player_x(), demoniac_x) - std::min(player.get_player_x(), demoniac_x);
    unsigned abs_y = std::max(player.get_player_y(), demoniac_y) - std::min(player.get_player_y(), demoniac_y);
    if(abs_x <= 1 && abs_y <= 1){
        return true;
    }
    return false;
}

void Enemy_demoniac::fighting(Player& player, Field& field){
    if(see_player(player)){
        player.set_health(player.get_health() > damage ? player.get_health() - damage : 0);
        std::stringstream ss;
        ss << "Player took damage from Demoniac " << player;
        Logger::logger_out().display(ss.str());
    }
}

void Enemy_demoniac::add_enemy(Cell& holder){
    holder.set_enemy(*this);
    demoniac_x = holder.get_cell_x();
    demoniac_y = holder.get_cell_y();
    holder.set_pass(false);
}
    
void Enemy_demoniac::move(Player& player, Field& field){
    if((count_move %4) == 0){
        count_move = 0;
        if(player.get_player_x() > demoniac_x && field.get_cell(demoniac_x+1, demoniac_y).get_pass()) dir = Right;
        else if(player.get_player_x() < demoniac_x && field.get_cell(demoniac_x-1, demoniac_y).get_pass()) dir = Left;
        else if(player.get_player_y() > demoniac_y && field.get_cell(demoniac_x, demoniac_y+1).get_pass()) dir = Down;
        else if(player.get_player_y() < demoniac_x && field.get_cell(demoniac_x, demoniac_y-1).get_pass()) dir = Up;
        
        if(dir == Up)
            move_up(player, field);
        else if(dir == Right)
            move_right(player, field);
        else if(dir == Down)
            move_down(player, field);
        else if(dir == Left)
            move_left(player, field);
        Logger::logger_out().display("Move demoniac");
    }
    else count_move++;
}

void Enemy_demoniac::move_up(Player& player, Field& field){
    if(!field.get_cell(demoniac_x, demoniac_y-1).get_pass() || 
    field.get_cell(demoniac_x, demoniac_y-1).pres_enemy() ||
    field.get_cell(demoniac_x, demoniac_y-1).pres_object() ||
    see_player(player) || field.get_cell(demoniac_x, demoniac_y-1).get_exit()){
        dir = Down;
        return;
    }
    field.get_cell(demoniac_x, demoniac_y).del_enemy();
    field.get_cell(demoniac_x, demoniac_y).set_pass(true);
    field.get_cell(demoniac_x, demoniac_y-1).set_enemy(*this);
    set_enemy_y(get_enemy_y() - 1);
    field.get_cell(demoniac_x, demoniac_y).set_pass(false);
}

void Enemy_demoniac::move_right(Player& player, Field& field){
    if(!field.get_cell(demoniac_x+1, demoniac_y).get_pass() || 
    field.get_cell(demoniac_x+1, demoniac_y).pres_enemy() ||
    field.get_cell(demoniac_x+1, demoniac_y).pres_object() ||
    see_player(player) || field.get_cell(demoniac_x+1, demoniac_y).get_exit()){
        dir = Left;
        return;
    }
    field.get_cell(demoniac_x, demoniac_y).del_enemy();
    field.get_cell(demoniac_x, demoniac_y).set_pass(true);
    field.get_cell(demoniac_x+1, demoniac_y).set_enemy(*this);
    set_enemy_x(get_enemy_x() + 1);
    field.get_cell(demoniac_x, demoniac_y).set_pass(false);
}

void Enemy_demoniac::move_down(Player& player, Field& field){
    if(!field.get_cell(demoniac_x, demoniac_y+1).get_pass() || 
    field.get_cell(demoniac_x, demoniac_y+1).pres_enemy() ||
    field.get_cell(demoniac_x, demoniac_y+1).pres_object() ||
    see_player(player) || field.get_cell(demoniac_x, demoniac_y+1).get_exit()){
        dir = Up;
        return;
    }
    field.get_cell(demoniac_x, demoniac_y).del_enemy();
    field.get_cell(demoniac_x, demoniac_y).set_pass(true);
    field.get_cell(demoniac_x, demoniac_y+1).set_enemy(*this);
    set_enemy_y(get_enemy_y() + 1);
    field.get_cell(demoniac_x, demoniac_y).set_pass(false);
}

void Enemy_demoniac::move_left(Player& player, Field& field){
    if(!field.get_cell(demoniac_x-1, demoniac_y).get_pass() || 
    field.get_cell(demoniac_x-1, demoniac_y).pres_enemy() ||
    field.get_cell(demoniac_x-1, demoniac_y).pres_object() ||
    see_player(player) || field.get_cell(demoniac_x-1, demoniac_y).get_exit()){
        dir = Right;
        return;
    }
    field.get_cell(demoniac_x, demoniac_y).del_enemy();
    field.get_cell(demoniac_x, demoniac_y).set_pass(true);
    field.get_cell(demoniac_x-1, demoniac_y).set_enemy(*this);
    set_enemy_x(get_enemy_x() - 1);
    field.get_cell(demoniac_x, demoniac_y).set_pass(false);
}

void Enemy_demoniac::check_death(Field& field, std::vector <Enemy*>& enemies, int i){
    if(health <= 0 || health > 50){
        health = 0;
        field.get_cell(demoniac_x, demoniac_y).del_enemy();
        field.get_cell(demoniac_x, demoniac_y).set_pass(true);
        enemies.erase(enemies.begin() + i);
    }
}

std::string Enemy_demoniac::get_class_name(){
    return "Enemy_demoniac";
}

Byte_array Enemy_demoniac::save(){
    Byte_array ba = Enemy::save();
    ba.put_object(health);
    ba.put_object(damage);
    ba.put_object(demoniac_x);
    ba.put_object(demoniac_y);
    ba.put_object(count_move);
    ba.put_object(dir);
    return ba;
}

void Enemy_demoniac::load(Byte_array& temp){
    Enemy::load(temp);
    temp.get_object(health);
    temp.get_object(damage);
    temp.get_object(demoniac_x);
    temp.get_object(demoniac_y);
    temp.get_object(count_move);
    temp.get_object(dir);
}