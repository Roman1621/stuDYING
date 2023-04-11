#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>

#define PRINT_DEBUG 2
#define HAS_SQUARE_LIST 

struct square{
	unsigned x, y;
	unsigned side;
};
//В этой статической переменной хранится частное решение в виде вектора квадратов
static std::vector<square> fill_set;

//Проверка: существует ли место для квадрата заданного размера? 
bool can_insert_square(const std::vector<std::vector<bool>>& map, const square& sq){
	if(sq.side == 0 || map.size() < sq.side + sq.y || map[sq.y].size() < sq.side + sq.x)
		return false;
	for(unsigned y = sq.y; y < sq.y + sq.side; ++y)
		for(unsigned x = sq.x; x < sq.x + sq.side; ++x)
			if(map[y][x])
				return false;
	return true;
}

//Поиск места для квадрата, игнорируя размер этого квадрата
std::pair<unsigned, unsigned> inline find_place_square(const std::vector<std::vector<bool>>& map, unsigned _y){
	unsigned N = map.size();
	for(unsigned y = _y; y < N; ++y)
		for(unsigned x = 0; x < N; ++x)
			if(!map[y][x])
				return {x, y};
	return {N, N};
}

//Вывод промежуточных результатов
void identr(unsigned lvl){
	for(unsigned i = 0; i < lvl; ++i)
		std::cout << "\t";
}

//Вывод битовой карты заполненности поля на экран
void print_map(const std::vector<std::vector<bool>>& map, unsigned lvl_ident = 0){
	for(unsigned y = 0; y < map.size(); ++y){
		identr(lvl_ident);
		for(unsigned x = 0; x < map.size(); ++x)
			std::cout << map[y][x] ? 'X' : ' ';
		std::cout << std::endl;
	}
}

//Вывод набора квадратов на экран
void print_square_set(const std::vector<square>& sq_set, unsigned lvl_ident = 0){
	for(const auto& sq : sq_set){
		identr(lvl_ident);
		std::cout << "x = " << sq.x << ", y = " << sq.y << ", side = " << sq.side << '\n';
	}
}

//Рекурсивная функция поиска решений
void solve_recur(unsigned N, const std::vector<square>& sq_set, const std::vector<std::vector<bool>>& map, unsigned cap, unsigned row, unsigned rec_lvl){
	if(!fill_set.empty() && sq_set.size() >= fill_set.size())
		return;

	std::pair<unsigned, unsigned> insc = find_place_square(map, row);
	unsigned x = insc.first, y = insc.second;
	if(x == N && y == N)
		return;//Поле заполнено

	for(unsigned side = N - 1 + N % 2; side > 0; --side){
		square new_sq{x, y, side}; //новый квадарат, который будет вставлен
		if(can_insert_square(map, new_sq)){
			std::vector<square> new_sq_set = sq_set; //новое частичное решение
			new_sq_set.push_back(new_sq);
			std::vector<std::vector<bool>> new_map = map; //новая битовая карта
			for(unsigned _y = y; _y < y + side; ++_y)
				for(unsigned _x = x; _x < x + side; ++_x)
					new_map[_y][_x] = true;
            //Осталось свободное пространство на поле
			if(cap > side*side){ 
				#if PRINT_DEBUG >= 2
				print_map(new_map, rec_lvl);
				identr(rec_lvl); std::cout << "recusion call for this map, added x = " << x << ", y = " << y << ", side = " << side << "\n";
				#endif
				solve_recur(N, new_sq_set, new_map, cap - side*side, y, rec_lvl + 1);
				#if PRINT_DEBUG >= 2
				identr(rec_lvl); std::cout << "end of recusion call, removed x = " << x << ", y = " << y << ", side = " << side << "\n";
				#endif
			}
            //Булева функция can_insert_square не нашла место для нового квадрата
			else{
				if(fill_set.empty() || new_sq_set.size() < fill_set.size()){
					#if PRINT_DEBUG >= 1
					#if PRINT_DEBUG >= 2
						identr(rec_lvl);
					#endif
					
                    if(fill_set.empty()) std::cout << "first solution of size ";
					else std::cout << "new solution of size ";
					std::cout << new_sq_set.size()<< "\n";
					print_square_set(new_sq_set, rec_lvl);
					#endif
					//Получено первое решение или новое решение "минимально"
					fill_set = new_sq_set;
				}
				return;
			}
		}
	}
}

void solve(unsigned N, std::vector<square> square_l = {}){
	std::vector<std::vector<bool>> map;
	std::vector<square> sq_set;

    //Оптимизации
	//Можем вычислить коэфициент, который заменит первоначальный
    //и позволит свести решение к решени задачи для квадрата меньшего размера
    //Будет использовано, если мы не задаём список квадратов, которые должны обязательно быть на поле
	unsigned K = 1;
	#ifndef HAS_SQUARE_LIST
    for(unsigned i = 2; K <= std::sqrt(N); ++i)
		if(!(N % i)){
			K = N / i;
			N = i;
			break;
		}
    #endif

	//В любое поле можно поместить три первоначальных квадрата
	#ifndef HAS_SQUARE_LIST
    unsigned init_side = (N+1) / 2;
	std::vector<bool> init_vec(init_side, false);
	for(unsigned i = 0; i < init_side; ++i)
		map.push_back(init_vec);
	map[0][0] = N > 2;	//Корректируем алгоритм при чётных сторонах поля
    #else
    std::vector<bool> vect(N, false);
	for(unsigned i = 0; i < N; ++i)
		map.push_back(vect);
    #endif

	#if PRINT_DEBUG >= 1 && !defined(HAS_SQUARE_LIST)
	std::cout << "Initial 3 squares placed in:\n";
	{
		std::vector<std::vector<bool>> dispmap;
		std::vector<bool> initv(N, false);
		for(unsigned i = 0; i < N; ++i)
			dispmap.push_back(initv);
		for(unsigned _y = 0; _y < 0 + init_side; ++_y)
			for(unsigned _x = 0; _x < 0 + init_side; ++_x)
				dispmap[_y][_x] = true;
		for(unsigned _y = 0; _y < 0 + init_side - N % 2; ++_y)
			for(unsigned _x = init_side; _x < init_side + init_side - N % 2; ++_x)
				dispmap[_y][_x] = true;
		for(unsigned _y = init_side; _y < init_side + init_side - N % 2; ++_y)
			for(unsigned _x = 0; _x < 0 + init_side - N % 2; ++_x)
				dispmap[_y][_x] = true;
		print_map(dispmap); std::cout << std::endl << std::endl;
	}
	#endif

    for(unsigned i = 0; i < square_l.size(); i++){
        square s = square_l[i];
        for(unsigned x = s.x; x < s.x + s.side; x++){
            for(unsigned y = s.y; y < s.y + s.side;y++){
                map[y][x] = true;
            }
        }
    }

	#ifndef HAS_SQUARE_LIST
	//Решения находятся для столешницы, не покрытой квадратами
    //Нужно сдвинуть начальные квадраты в левый верхний угол
    solve_recur(init_side, sq_set, map, init_side * init_side - N % 2, 0, 0);
	for(auto& sq : fill_set){
		sq.x += init_side - N % 2;
		sq.y += init_side - N % 2;
	}
    //Добавляем три "базовых" квадрата в решение 
	fill_set.push_back({0, 0, init_side});
	fill_set.push_back({init_side, 0, init_side - N % 2});
	fill_set.push_back({0, init_side, init_side - N % 2});
    #else
    unsigned area = 0;
    for(unsigned i = 0; i < square_l.size(); i++){
        area = area + square_l[i].side*square_l[i].side;
    }
    solve_recur(N, sq_set, map, N*N - area, 0, 0);
    #endif

    for(unsigned i = 0; i < square_l.size(); i++){
        fill_set.push_back(square_l[i]);
    }

	for(auto& sq : fill_set){
		sq.x = sq.x * K + 1;
		sq.y = sq.y * K + 1;
		sq.side *= K;
	}
}

int main(){
	unsigned N;
	std::cin >> N;
    
    //Задан список квадратов
    #ifdef HAS_SQUARE_LIST 
    unsigned numb;
    std::cin >> numb;
    std::vector<square> square_list;
    for(unsigned i = 0; i < numb; i++){
        square s;
        std::cin >> s.x >> s.y >> s.side;
        square_list.push_back(s);
    }
    solve(N, square_list);
    //Не задан список квадратов
    #else 
	solve(N);
    #endif

	std::cout << fill_set.size() << '\n';
	for(const auto& sq : fill_set)
		std::cout << sq.x << ' ' << sq.y << ' ' << sq.side << '\n';
	return 0;
}