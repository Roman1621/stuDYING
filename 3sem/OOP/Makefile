GCPP = g++ -std=c++17 -g


game: game.o bind.o death_rule.o exit_rule.o cell_objects.o cell_object_view.o enemy.o game_rule.o cell.o save.o save_exception.o class_creator.o cell_view.o enemy_demoniac.o enemy_imp.o enemy_knight.o field_view.o field.o object_damage.o fstream_wrapper.o input.o object_heal.o object_trap.o logger.o ostream_wrapper.o player.o
	g++ -g sources/main.cpp $^ -o $@

clean:
	-rm -f *.o

game.o: sources/game.cpp headers/game.h
	g++ -g -c $< -o $@
bind.o: sources/bind.cpp headers/bind.h
	g++ -g -c $< -o $@
game_rule.o: sources/game_rule.cpp headers/game_rule.h
	g++ -g -c $< -o $@
save.o: sources/save.cpp headers/save.h
	g++ -g -c $< -o $@
save_exception.o: sources/save_exception.cpp headers/save_exception.h
	g++ -g -c $< -o $@
class_creator.o: sources/class_creator.cpp headers/class_creator.h
	g++ -g -c $< -o $@
input.o: sources/input.cpp headers/input.h
	g++ -g -c $< -o $@
exit_rule.o: sources/exit_rule.cpp headers/exit_rule.h
	g++ -g -c $< -o $@
death_rule.o: sources/death_rule.cpp headers/death_rule.h
	g++ -g -c $< -o $@
cell_objects.o: sources/cell_objects.cpp headers/cell_objects.h
	g++ -g -c $< -o $@
cell_object_view.o: sources/cell_object_view.cpp headers/cell_object_view.h
	g++ -g -c $< -o $@
cell.o: sources/cell.cpp headers/cell.h
	g++ -g -c $< -o $@
cell_view.o: sources/cell_view.cpp headers/cell_view.h
	g++ -g -c $< -o $@
enemy.o: sources/enemy.cpp headers/enemy.h
	g++ -g -c $< -o $@
enemy_demoniac.o: sources/enemy_demoniac.cpp headers/enemy_demoniac.h
	g++ -g -c $< -o $@
enemy_imp.o: sources/enemy_imp.cpp headers/enemy_imp.h
	g++ -g -c $< -o $@
enemy_knight.o: sources/enemy_knight.cpp headers/enemy_knight.h
	g++ -g -c $< -o $@
field.o: sources/field.cpp headers/field.h
	g++ -g -c $< -o $@
field_view.o: sources/field_view.cpp headers/field_view.h
	g++ -g -c $< -o $@
fstream_wrapper.o: sources/fstream_wrapper.cpp headers/fstream_wrapper.h
	g++ -g -c $< -o $@
object_damage.o: sources/object_damage.cpp headers/object_damage.h
	g++ -g -c $< -o $@
object_heal.o: sources/object_heal.cpp headers/object_heal.h
	g++ -g -c $< -o $@
object_trap.o: sources/object_trap.cpp headers/object_trap.h
	g++ -g -c $< -o $@
logger.o: sources/logger.cpp headers/logger.h
	g++ -g -c $< -o $@
ostream_wrapper.o: sources/ostream_wrapper.cpp headers/ostream_wrapper.h
	g++ -g -c $< -o $@
player.o: sources/player.cpp headers/player.h
	g++ -g -c $< -o $@