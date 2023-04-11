#ifndef GAME_H
#define GAME_H

#include "..//headers/field_view.h"
#include "..//headers/field.h"
#include "..//headers/object_damage.h"
#include "..//headers/object_heal.h"
#include "..//headers/object_trap.h"
#include "..//headers/player.h"
#include "..//headers/enemy.h"
#include "..//headers/enemy_demoniac.h"
#include "..//headers/enemy_imp.h"
#include "..//headers/enemy_knight.h"
#include "fstream_wrapper.h"
#include "logger.h"
#include "exit_rule.h"
#include "death_rule.h"
#include "input.h"

template <typename win_rule_type, typename lose_rule_type, size_t difficulty>
class Game{
    public:
        ~Game();
        void clear_screen();
        void on_start();

        void input(char user_input, Player& player, Field& field, const std::vector<Enemy*>& enemy);
        void update_screen();

        void add_enemy_on_field(std::vector<Enemy*>& enemy);
        std::vector<Enemy*>& get_enemy();
        Field& get_field();
        Player& get_player();
        win_rule_type& get_win_rule();
        lose_rule_type& get_lose_rule();

        void save(const char* save_name);
        void load(const char* load_name);

    private:
        win_rule_type win_rule;
        lose_rule_type lose_rule;
        std::vector<Enemy*> enemy;
        std::vector<Object*> object;
        Field* field;
        Player* player;
        Input input_ex;
        Field_view* print;
        Cell* entrance;
};

#endif