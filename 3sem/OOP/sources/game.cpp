#include "..//headers/game.h"
/*
template <typename win_rule_type, typename lose_rule_type>
Game<win_rule_type, lose_rule_type>::Game(Game_rule& win, Game_rule& lose) : win(win), lose(lose){}
*/
template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
void Game<win_rule_type, lose_rule_type, difficulty>::clear_screen(){
    std::cout << "\033[H\033[J";
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
void Game<win_rule_type, lose_rule_type, difficulty>::input(char user_input, Player& player, Field& field, const std::vector<Enemy*>& enemy){
    if(Bind::get_key("Exit") == user_input)
        return;
    else if(Bind::get_key("Up") == user_input)
        player.move_up(field);
    else if(Bind::get_key("Right") == user_input)
        player.move_right(field);
    else if(Bind::get_key("Down") == user_input)
        player.move_down(field);
    else if(Bind::get_key("Left") == user_input)
        player.move_left(field);
    else if(Bind::get_key("Fighting") == user_input)
        player.fighting(field);
    else if(Bind::get_key("Save") == user_input)
        save("Save_game");
    else if(Bind::get_key("Load") == user_input)
        load("Save_game");
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
Game<win_rule_type, lose_rule_type, difficulty>::~Game(){
    for(auto i = object.begin(); i != object.end(); i++) delete *i;
    for(auto i = enemy.begin(); i != enemy.end(); i++) delete *i;
    delete field;
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
void Game<win_rule_type, lose_rule_type, difficulty>::update_screen(){
    OWrapper cout_window(std::cout);
    std::ofstream file_out;
    FWrapper file_window_out(file_out, "game_out");
    Logger::init(Default, {file_window_out, cout_window});
    Logger::init(Console, {cout_window});
    Logger::init(File, {file_window_out});
    print = new Field_view (*field);

    char user_input = 0;
    print->display();
    user_input = input_ex.get_input();
    input(user_input, *player, *field, enemy);
    clear_screen();
    while(1){
        print->display();
        if(win_rule.done()){
            std::cout << "EXIT!" << std::endl;
            return;
        }
        if(lose_rule.done()){
            std::cout << "DEAD!" << std::endl;
            return;
        }

        for(int i = 0; i < object.size(); i++){
            object.at(i)->player_pass(*player, *field);
            object.at(i)->check_take(*field, object, i);
        }

        for(int i = 0; i < enemy.size(); i++){
            enemy.at(i)->fighting(*player, *field);
            enemy.at(i)->move(*player, *field);
            enemy.at(i)->check_death(*field, enemy, i);
        }

        Logger::logger_out(Default).display("");
        user_input = input_ex.get_input();
        input(user_input, *player, *field, enemy);
        clear_screen();
    }
    
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
void Game<win_rule_type, lose_rule_type, difficulty>::add_enemy_on_field(std::vector<Enemy*>& enemy){
    enemy.push_back(new Enemy_demoniac);
    enemy.push_back(new Enemy_imp);
    enemy.push_back(new Enemy_knight);
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
std::vector<Enemy*>& Game<win_rule_type, lose_rule_type, difficulty>::get_enemy(){
    return enemy;
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
Field& Game<win_rule_type, lose_rule_type, difficulty>::get_field(){
    return *field;
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
Player& Game<win_rule_type, lose_rule_type, difficulty>::get_player(){
    return *player;
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
win_rule_type& Game<win_rule_type, lose_rule_type, difficulty>::get_win_rule(){
    return win_rule;
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
lose_rule_type& Game<win_rule_type, lose_rule_type, difficulty>::get_lose_rule(){
    return lose_rule;
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
void Game<win_rule_type, lose_rule_type, difficulty>::on_start(){
    clear_screen();
    //int choose_dif = 0;
    //std::cout << "Choose difficulty: 1 - Easy, 2 - Normal, 3 - Hard: ";
    //std::cin >> difficulty; 
    if(difficulty == 1){
        field = new Field((unsigned) 20, (unsigned)20);
    }
    else if(difficulty == 2){
        field = new Field((unsigned) 12, (unsigned) 12); 
    }
    else if(difficulty == 3){
        field = new Field((unsigned) 7,(unsigned) 7);
    }

    object.push_back(new Object_damage);
    object.push_back(new Object_heal);
    object.push_back(new Object_trap);
    add_enemy_on_field(enemy);

    entrance = &field->put_exit(2);
    field->put_enemy(enemy);
    field->put_object(object);

    player = new Player;
    player->set_player_x(entrance->get_cell_x());
    player->set_player_y(entrance->get_cell_y());
    field->get_cell(player->get_player_x(), player->get_player_y()).set_display('P');
    entrance->set_player(*player);
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
void Game<win_rule_type, lose_rule_type, difficulty>::save(const char* save_name){
    std::fstream fs;
    fs.open(save_name, std::fstream::out | std::fstream::trunc);
    
    try{
        Byte_array ba = field->save();
        ba.write_out(fs);
    }

    catch(std::exception &e){
        std::string message = e.what();
        Logger::logger_out(Console).display(message);
    }
    fs.close();
}

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
void Game<win_rule_type, lose_rule_type, difficulty>::load(const char* load_name){
    std::fstream fs;
    fs.open(load_name,std::fstream::in);
    Field* field_new;

    try{
        Byte_array ba;
        ba.read_in(fs);
        field_new = (Field*)Class_creator::get_object(ba);
    }
    catch(std::exception &e){
        std::string message = e.what();
        Logger::logger_out(Console).display(message);
        return;
    }
    delete field;
    field = field_new;
    delete print;
    print = new Field_view (*field);
    win_rule.set_field(*field);
    lose_rule.set_field(*field);
    enemy.clear();
    object.clear();
    for(int x = 0; x < field->get_x(); x++){
        for(int y = 0; y < field->get_y(); y++){
            if(field->get_cell(x, y).pres_object()){
                object.push_back((Object*) &field->get_cell(x, y).get_object());
            }
            if(field->get_cell(x, y).pres_player()){
                player = (Player*) &field->get_cell(x, y).get_player();
            }
            if(field->get_cell(x, y).pres_enemy()){
                enemy.push_back((Enemy*) &field->get_cell(x, y).get_enemy());
            }
        }
    }
    win_rule.set_player(*player);
    lose_rule.set_player(*player);
}