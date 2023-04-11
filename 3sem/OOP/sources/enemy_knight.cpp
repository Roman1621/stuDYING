#include "..//headers/enemy_knight.h"
#include "..//headers/field.h"
#include "..//headers/logger.h"
#include <cstdlib>
#include <random>
#include <tuple>
#include <sstream>

Enemy_knight::Enemy_knight(){
    init();
}

void Enemy_knight::init(){
    cell_view = new Cell_object_view('K', *this);
}

unsigned int Enemy_knight::get_enemy_x() const{
    return knight_x;
}

unsigned int Enemy_knight::get_enemy_y() const{
    return knight_y;
}

void Enemy_knight::set_enemy_x(unsigned int knight_x){
    this->knight_x = knight_x;
}

void Enemy_knight::set_enemy_y(unsigned int knight_y){
    this->knight_y = knight_y;
}

unsigned int Enemy_knight::get_health() const{
    return health;
}

void Enemy_knight::set_health(unsigned int health_sp){
    health = health_sp;
}

bool Enemy_knight::see_player(Player& player){
    unsigned abs_x = std::max(player.get_player_x(), knight_x) - std::min(player.get_player_x(), knight_x);
    unsigned abs_y = std::max(player.get_player_y(), knight_y) - std::min(player.get_player_y(), knight_y);
    if(abs_x <= 2 && abs_y <= 2){
        return true;
    }
    return false;
}

void Enemy_knight::fighting(Player& player, Field& field){
    if(see_player(player)){
        player.set_health(player.get_health() > damage ? player.get_health() - damage : 0);
        std::stringstream ss;
        ss << "Player took damage from Knight " << player;
        Logger::logger_out().display(ss.str());
    }
}

void Enemy_knight::add_enemy(Cell& holder){
    holder.set_enemy(*this);
    knight_x = holder.get_cell_x();
    knight_y = holder.get_cell_y();
    holder.set_pass(false);
}
    
void Enemy_knight::move(Player& player, Field& field){
    if(count_move % 3 == 0){
        std::mt19937 generator;
    	std::random_device rand;
    	generator.seed(rand());
    	std::uniform_int_distribution<> direction(0, 3);
		dir = (dir_of_move)direction(generator);
    }
    if(count_move % 15 == 0)
        count_move = 0;

    if(dir == Up)
        move_up(player, field);
    else if(dir == Right)
        move_right(player, field);
    else if(dir == Down)
        move_down(player, field);
    else if(dir == Left)
        move_left(player, field);
    count_move++;

    Logger::logger_out().display("Knight move");
}

void Enemy_knight::move_up(Player& player, Field& field){
    if(!field.get_cell(knight_x, knight_y-1).get_pass() || 
    field.get_cell(knight_x, knight_y-1).pres_enemy() ||
    field.get_cell(knight_x, knight_y-1).pres_object() ||
    see_player(player) || field.get_cell(knight_x, knight_y-1).get_exit()){
        dir = Down;
        return;
    }
    field.get_cell(knight_x, knight_y).del_enemy();
    field.get_cell(knight_x, knight_y).set_pass(true);
    field.get_cell(knight_x, knight_y-1).set_enemy(*this);
    set_enemy_y(get_enemy_y() - 1);
    field.get_cell(knight_x, knight_y).set_pass(false);
}

void Enemy_knight::move_right(Player& player, Field& field){
    if(!field.get_cell(knight_x+1, knight_y).get_pass() || 
    field.get_cell(knight_x+1, knight_y).pres_enemy() ||
    field.get_cell(knight_x+1, knight_y).pres_object() ||
    see_player(player) || field.get_cell(knight_x+1, knight_y).get_exit()){
        dir = Left;
        return;
    }
    field.get_cell(knight_x, knight_y).del_enemy();
    field.get_cell(knight_x, knight_y).set_pass(true);
    field.get_cell(knight_x+1, knight_y).set_enemy(*this);
    set_enemy_x(get_enemy_x() + 1);
    field.get_cell(knight_x, knight_y).set_pass(false);
}

void Enemy_knight::move_down(Player& player, Field& field){
    if(!field.get_cell(knight_x, knight_y+1).get_pass() || 
    field.get_cell(knight_x, knight_y+1).pres_enemy() ||
    field.get_cell(knight_x, knight_y+1).pres_object() ||
    see_player(player) || field.get_cell(knight_x, knight_y+1).get_exit()){
        dir = Up;
        return;
    }
    field.get_cell(knight_x, knight_y).del_enemy();
    field.get_cell(knight_x, knight_y).set_pass(true);
    field.get_cell(knight_x, knight_y+1).set_enemy(*this);
    set_enemy_y(get_enemy_y() + 1);
    field.get_cell(knight_x, knight_y).set_pass(false);
}

void Enemy_knight::move_left(Player& player, Field& field){
    if(!field.get_cell(knight_x-1, knight_y).get_pass() || 
    field.get_cell(knight_x-1, knight_y).pres_enemy() ||
    field.get_cell(knight_x-1, knight_y).pres_object() ||
    see_player(player) || field.get_cell(knight_x-1, knight_y).get_exit()){
        dir = Right;
        return;
    }
    field.get_cell(knight_x, knight_y).del_enemy();
    field.get_cell(knight_x, knight_y).set_pass(true);
    field.get_cell(knight_x-1, knight_y).set_enemy(*this);
    set_enemy_x(get_enemy_x() - 1);
    field.get_cell(knight_x, knight_y).set_pass(false);
}

void Enemy_knight::check_death(Field& field, std::vector <Enemy*>& enemies, int i){
    if(health <= 0 || health > 100){
        health = 0;
        field.get_cell(knight_x, knight_y).del_enemy();
        field.get_cell(knight_x, knight_y).set_pass(true);
        enemies.erase(enemies.begin() + i);
    }
}



/*Enemy_knight::~Enemy_knight(){
    if(cell_view)
        delete cell_view;
}*/

std::string Enemy_knight::get_class_name(){
    return "Enemy_knight";
}

Byte_array Enemy_knight::save(){
    Byte_array ba = Enemy::save();
    ba.put_object(health);
    ba.put_object(damage);
    ba.put_object(knight_x);
    ba.put_object(knight_y);
    ba.put_object(count_move);
    ba.put_object(dir);
    return ba;
}

void Enemy_knight::load(Byte_array& temp){
    Enemy::load(temp);
    temp.get_object(health);
    temp.get_object(damage);
    temp.get_object(knight_x);
    temp.get_object(knight_y);
    temp.get_object(count_move);
    temp.get_object(dir);
}