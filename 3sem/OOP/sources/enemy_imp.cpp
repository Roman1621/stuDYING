#include "..//headers/enemy_imp.h"
#include "..//headers/field.h"
#include "..//headers/logger.h"
#include <cstdlib>
#include <random>
#include <tuple>
#include <sstream>

Enemy_imp::Enemy_imp(){
    init();
}

unsigned int Enemy_imp::get_enemy_x() const{
    return imp_x;
}

unsigned int Enemy_imp::get_enemy_y() const{
    return imp_y;
}

void Enemy_imp::set_enemy_x(unsigned int imp_x){
    this->imp_x = imp_x;
}

void Enemy_imp::set_enemy_y(unsigned int imp_y){
    this->imp_y = imp_y;
}

unsigned int Enemy_imp::get_health() const{
    return health;
}

void Enemy_imp::set_health(unsigned int health_sp){
    health = health_sp;
}

bool Enemy_imp::see_player(Player& player){
    unsigned abs_x = std::max(player.get_player_x(), imp_x) - std::min(player.get_player_x(),imp_x);
    unsigned abs_y = std::max(player.get_player_y(), imp_y) - std::min(player.get_player_y(), imp_y);
    if(abs_x <= 2 && abs_y <= 2){
        return true;
    }
    return false;
}

void Enemy_imp::fighting(Player& player, Field& field){
    if(see_player(player)){
        player.set_health(player.get_health() > damage ? player.get_health() - damage : 0);
        std::stringstream ss;
        ss << "Player took damage from Imp " << player;
        Logger::logger_out().display(ss.str());
    }
}

void Enemy_imp::add_enemy(Cell& holder){
    holder.set_enemy(*this);
    imp_x = holder.get_cell_x();
    imp_y = holder.get_cell_y();
    holder.set_pass(false);
    Logger::logger_out().display("Imp on field");
}

void Enemy_imp::move(Player& player, Field& field){}

void Enemy_imp::check_death(Field& field, std::vector <Enemy*>& enemies, int i){
    if(health <= 0 || health > 100){
        health = 0;
        field.get_cell(imp_x, imp_y).del_enemy();
        field.get_cell(imp_x, imp_y).set_pass(true);
        enemies.erase(enemies.begin() + i);
    }
}

void Enemy_imp::init(){
    cell_view = new Cell_object_view('I', *this);
}

/*Enemy_imp::~Enemy_imp(){
    if(cell_view)
        delete cell_view;
}*/