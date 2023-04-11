#include <iostream>
#include <vector>
#include <string>
#include <queue> 
#include <algorithm>

//#define DEBUG
//#define IND

struct vert;

//Структура, отвечающая за хранение рёбер графа
struct edge{
	vert* to;
	double weight;
};

//Структура, отвечающая за хранение вершин графа
struct vert{
	char symb;
	std::vector<edge> edges;
	unsigned char visited;
	double dist, euristic_dist;
	vert* parent;
};

//Класс-компоратор. Необходим для корректного построения очереди с приоритетом
class comp{
	public:
		bool operator()(vert*& a, vert*& b){
			if((a->dist + a->euristic_dist) == (b->dist + b->euristic_dist)) return a->symb < b->symb;
			return a->dist + a->euristic_dist > b->dist + b->euristic_dist;
		}
};

#ifndef IND
//Основная функция, в которой и происходит поиск пути в графе
std::vector<vert*> a_star(vert* start, vert* finish){
	//Инициализируем очередь с приоритетом
	std::priority_queue<vert*, std::vector<vert*>, comp> open;
	open.push(start);
	/*std::vector<vert*> open_massive;
	open_massive.push_back(start);*/
	//Пока очередь не пустая
	while(!open.empty()){
		//Извлекаем вершину
		vert* v = open.top();
		open.pop();
		//open_massive.erase(std::find(open_massive.begin(), open_massive.end(), v));
		#ifdef DEBUG
		std::cout << "\nVisting vertice " << v->symb << ":\n";
		#endif
		//Отмечаем её пройденной
		if(v->visited)
			continue;
		v->visited = 1;

		//Если текущая извлеченная вершина конечная, то строим путь и возвращаем его значение
		if(v == finish){
			#ifdef DEBUG
			std::cout << "\tReached finish node\n";
			#endif
			std::vector<vert*> ret;
			while(v != start){
				ret.push_back(v);
				v = v->parent;
			}
			ret.push_back(start);
			return ret;
		}

		//Проходимся по всем ребрам вершины
		for(size_t i = 0; i < v->edges.size(); ++i){
			//считаем новые значения эвристической функции
			double new_dist = v->dist + v->edges[i].weight;
			double new_euristic_dist = finish->symb > v->edges[i].to->symb ? (finish->symb - v->edges[i].to->symb) : (v->edges[i].to->symb - finish->symb);
			//Если новые значения меньше старых
			//То изменяем старые данные на новые
			if((!v->edges[i].to->visited  && v->edges[i].to->dist > new_dist)|| v->edges[i].to->dist == 0){
				v->edges[i].to->parent = v;
				v->edges[i].to->dist = new_dist;
				v->edges[i].to->euristic_dist = new_euristic_dist;
				//Проверяем есть ли новая вершина в очереди
				int in_queue = 0;
				/*for(size_t j = 0; j < open_massive.size(); ++j)
					if(open_massive[j] == v->edges[i].to)
					{ in_queue = 1; break; }*/
				if(!in_queue){
					open.push(v->edges[i].to);
					//open_massive.push_back(v->edges[i].to);
					#ifdef DEBUG
					printf("\tAdding vertice to queue: %c\tdist: %-6.2lf\theur. dist: %-6.2lf\tparent: %c\n", v->edges[i].to->symb, v->edges[i].to->dist, v->edges[i].to->euristic_dist, v->edges[i].to->parent->symb);
					#endif
				}
				else{
					#ifdef DEBUG
					printf("\tUpdating vertice: %c\t\tdist: %-6.2lf\theur. dist: %-6.2lf\tparent: %c\n", v->edges[i].to->symb, v->edges[i].to->dist, v->edges[i].to->euristic_dist, v->edges[i].to->parent->symb);
					#endif
				}
			}
		}
	}
	return {};
}
#else
//Основная функция с учётом индивидуализации
std::vector<vert*> a_star(vert* start, vert* finish, vert* finish2){
	std::priority_queue<vert*, std::vector<vert*>, comp> open;
	open.push(start);

	std::vector<vert*> open_massive;
	open_massive.push_back(start);
	while(!open.empty()){
		vert* v = open.top();
		open.pop();
		open_massive.erase(std::find(open_massive.begin(), open_massive.end(), v));
		#ifdef DEBUG
		std::cout << "\nVisting vertice " << v->symb << ":\n";
		#endif
		if(v->visited)
			continue;
		v->visited = 1;

		if(v == finish || v == finish2){
			#ifdef DEBUG
			std::cout << "\tReached finish node\n";
			#endif
			std::vector<vert*> ret;
			while(v != start){
				ret.push_back(v);
				v = v->parent;
			}
			ret.push_back(start);
			return ret;
		}
		for(size_t i = 0; i < v->edges.size(); ++i){
			//считаем новые значения эвристической функции
			double new_dist = v->dist + v->edges[i].weight;
			double new_euristic_dist = finish->symb > v->edges[i].to->symb ? (finish->symb - v->edges[i].to->symb) : (v->edges[i].to->symb - finish->symb);
			double new_euristic_dist2 = finish2->symb > v->edges[i].to->symb ? (finish2->symb - v->edges[i].to->symb) : (v->edges[i].to->symb - finish2->symb);
			//Если новые значения меньше старых
			//То изменяем старые данные на новые
			if((!v->edges[i].to->visited  && v->edges[i].to->dist > new_dist)|| v->edges[i].to->dist == 0){
				v->edges[i].to->parent = v;
				v->edges[i].to->dist = new_dist;
				v->edges[i].to->euristic_dist = new_euristic_dist;
				//Проверяем есть ли новая вершина в очереди
				int in_queue = 0;
				for(size_t j = 0; j < open_massive.size(); ++j)
					if(open_massive[j] == v->edges[i].to)
					{ in_queue = 1; break; }
				if(!in_queue){
					open.push(v->edges[i].to);
					open_massive.push_back(v->edges[i].to);
					#ifdef DEBUG
					printf("\tAdding vertice to queue: %c\tdist: %-6.2lf\theur. dist: %-6.2lf\tparent: %c\n", v->edges[i].to->symb, v->edges[i].to->dist, v->edges[i].to->euristic_dist, v->edges[i].to->parent->symb);
					#endif
				}
				else{
					#ifdef DEBUG
					printf("\tUpdating vertice: %c\t\tdist: %-6.2lf\theur. dist: %-6.2lf\tparent: %c\n", v->edges[i].to->symb, v->edges[i].to->dist, v->edges[i].to->euristic_dist, v->edges[i].to->parent->symb);
					#endif
				}
			}
		}
	}
	return {};
}
#endif

int main(){
	char start_ch, finish_ch, finish_ch2;
	vert verts['z' - 'a' + 1];
	//инициализируем все основные данные нулями
	for(size_t i = 0; i < 'z' - 'a' + 1; i++) verts[i].symb =verts[i].visited = verts[i].euristic_dist = verts[i].dist = 0;

	//ввод данных
	scanf("%c %c", &start_ch, &finish_ch);
	#if defined IND
	scanf(" %c", &finish_ch2);
	#endif
	vert *start = verts + (start_ch - 'a'), *finish = verts + (finish_ch - 'a');
	start->symb = start_ch;
	finish->symb = finish_ch;
	#ifdef IND
	vert *finish2 = verts + (finish_ch2 - 'a');
	finish2->symb = finish_ch2;
	#endif

	char from_ch, to_ch; double e_weight;
	while(scanf(" %c %c%lf", &from_ch, &to_ch, &e_weight) == 3){
		vert* from = verts + (from_ch - 'a');
		vert* to = verts + (to_ch - 'a');

		if(!from->symb) from->symb = from_ch;
		if(!to->symb) to->symb = to_ch;

		from->edges.push_back({to, e_weight});
	}

	#ifdef DEBUG
	std::cout << "A* path search:\n";
	#endif
	#ifdef IND
	std::vector<vert*> res = a_star(start, finish, finish2);
	#else
	std::vector<vert*> res = a_star(start, finish);
	#endif
	#ifdef DEBUG
	std::cout << "\nResulting path: ";
	#endif
	//Вывод результатов
	if(res.size()){
		for(size_t i = res.size() - 1;; --i){
			std::cout << res[i]->symb;
			if(i == 0) break;
		}
	}
	//Если путь не найден
	#ifndef IND
	else
		std::cout << "Path from " << start_ch << " to " << finish_ch << " doesn't exist in this graph.";
	#else
	else std::cout << "Path from " << start_ch << " to " << finish_ch << " and to " << finish_ch2 << " doesn't exist in this graph.";
	#endif
	std::cout << '\n';
}