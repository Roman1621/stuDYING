#include "..//headers/player.h"
#include "..//headers/field.h"
#include "..//headers/logger.h"
#include <sstream>

Player::Player(){
    init();
}

void Player::init(){
    cell_view = new Cell_object_view('P', *this);
}

/*Player::~Player(){
    if(cell_view)
        delete cell_view;
}*/

unsigned int Player::get_player_x() const{
    return player_x;
}

unsigned int Player::get_player_y() const{
    return player_y;
}

void Player::set_player_x(unsigned int player_x){
    this->player_x = player_x;
}

void Player::set_player_y(unsigned int player_y){
    this->player_y = player_y;
}

unsigned int Player::get_damage() const{
    return damage;
}

void Player::set_damage(unsigned int damage){
    this->damage = damage;
}

unsigned int Player::get_health() const{
    return health;
}

void Player::set_health(unsigned int health){
    this->health = health;
}

bool Player::check_death(Field& field){
    if(health <= 0 || health > 100){
        health = 0;
        field.get_cell(player_x, player_y).set_pass(true);
        return true;
    }
    else
        return false;
}

void Player::move_up(Field& field){
    if(get_player_y() != 0 && field.get_cell(get_player_x(), get_player_y()-1).get_pass()){
		field.get_cell(get_player_x(), get_player_y()).set_pass(true);
        field.get_cell(get_player_x(), get_player_y()).del_player();
		field.get_cell(get_player_x(), get_player_y()-1).set_player(*this);
        field.get_cell(get_player_x(), get_player_y()-1).set_pass(false);
		set_player_y(get_player_y()-1);
        std::stringstream ss;
        ss << *this << " move Up";
        Logger::logger_out().display(ss.str());
	}
}

void Player::move_right(Field& field){
    if(get_player_x() != field.get_x()-1 && field.get_cell(get_player_x()+1, get_player_y()).get_pass()){
		field.get_cell(get_player_x(), get_player_y()).set_pass(true);
        field.get_cell(get_player_x(), get_player_y()).del_player();
		field.get_cell(get_player_x()+1, get_player_y()).set_player(*this);
        field.get_cell(get_player_x()+1, get_player_y()).set_pass(false);
		set_player_x(get_player_x()+1);
        std::stringstream ss;
        ss << *this << " move Right";
        Logger::logger_out().display(ss.str());
	}
}

void Player::move_down(Field& field){
    if(get_player_y() != field.get_y()-1 && field.get_cell(get_player_x(), get_player_y()+1).get_pass()){
		field.get_cell(get_player_x(), get_player_y()).set_pass(true);
        field.get_cell(get_player_x(), get_player_y()).del_player();
		field.get_cell(get_player_x(), get_player_y()+1).set_player(*this);
        field.get_cell(get_player_x(), get_player_y()+1).set_pass(false);
		set_player_y(get_player_y()+1);
        std::stringstream ss;
        ss << *this << " move Down";
        Logger::logger_out().display(ss.str());
	}
}

void Player::move_left(Field& field){
    if(get_player_x() != 0 && field.get_cell(get_player_x()-1, get_player_y()).get_pass()){
		field.get_cell(get_player_x(), get_player_y()).set_pass(true);
        field.get_cell(get_player_x(), get_player_y()).del_player();
		field.get_cell(get_player_x()-1, get_player_y()).set_player(*this);
        field.get_cell(get_player_x()-1, get_player_y()).set_pass(false);
		set_player_x(get_player_x()-1);
        std::stringstream ss;
        ss << *this << " move Left";
        Logger::logger_out().display(ss.str());
	}
}

void Player::fighting(Field& field){

        for(unsigned x = (player_x >= 2 ? player_x - 2 : 0);
                x < (player_x + 2 < field.get_x() ? player_x + 2 : field.get_x());
                ++x)
        {
            for(unsigned y = (player_y >= 2 ? player_y - 2 : 0);
                    y < (player_y + 2 < field.get_y() ? player_y + 2 : field.get_y()-1);
                    ++y)
            {
                if(field.get_cell(x, y).pres_enemy()){
                    Enemy& e = (Enemy&)field.get_cell(x, y).get_enemy();
                    e.set_health(e.get_health() > damage ? e.get_health() - damage : 0);
                    Logger::logger_out().display("Enemy took damage from player");
                }
            }
        }
}

std::ostream& operator<<(std::ostream& ostr, const Player& player){
    ostr  << " health: " << player.get_health()
    << " damage: " << player.get_damage()
    << " Pos_Player_X: " << player.get_player_x()
    << " Pos_Player_Y: " << player.get_player_y();
    return ostr;
}

std::string Player::get_class_name(){
    return "Player";
}

Byte_array Player::save(){
    Byte_array ba = Cell_objects::save();
    ba.put_object(health);
    ba.put_object(damage);
    ba.put_object(player_x);
    ba.put_object(player_y);
    return ba;
}

void Player::load(Byte_array& temp){
    Cell_objects::load(temp);
    temp.get_object(health);
    temp.get_object(damage);
    temp.get_object(player_x);
    temp.get_object(player_y);
}