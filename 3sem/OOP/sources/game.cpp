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
    if(user_input == 'q')
        return;
    else if(user_input == 'w')
        player.move_up(field);
    else if(user_input == 'd')
            player.move_right(field);
    else if(user_input == 's')
        player.move_down(field);
    else if(user_input == 'a')
        player.move_left(field);
    else if(user_input == 'f')
        player.fighting(field);
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
    Field_view print(*field);

    int user_input = 0;
    print.display();
    user_input = fgetc(stdin);
    input(user_input, player, *field, enemy);
    clear_screen();
    while(1){
        print.display();
        if(win_rule.done()){
            std::cout << "EXIT!" << std::endl;
            return;
        }
        if(lose_rule.done()){
            std::cout << "DEAD!" << std::endl;
            return;
        }

        for(int i = 0; i <object.size(); i++){
            object.at(i)->player_pass(player, *field);
            object.at(i)->check_take(*field, object, i);
        }

        for(int i = 0; i < enemy.size(); i++){
            enemy.at(i)->fighting(player, *field);
            enemy.at(i)->move(player, *field);
            enemy.at(i)->check_death(*field, enemy, i);
        }

        Logger::logger_out(Default).display("");
        user_input = fgetc(stdin);
        input(user_input, player, *field, enemy);
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
    return player;
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

    std::vector <Object*> object;
    object.push_back(new Object_damage);
    object.push_back(new Object_heal);
    object.push_back(new Object_trap);
    add_enemy_on_field(enemy);

    Cell& entrance = field->put_exit(2);
    field->put_enemy(enemy);
    field->put_object(object);

    player.set_player_x(entrance.get_cell_x());
    player.set_player_y(entrance.get_cell_y());
    field->get_cell(player.get_player_x(), player.get_player_y()).set_display('P');
    entrance.set_player(player);
}