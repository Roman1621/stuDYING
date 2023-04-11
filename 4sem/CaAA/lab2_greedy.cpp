#include <iostream>
#include <vector>
#include <string>
#include <queue> 

#define DEBUG

struct vert;

//Структура, отвечающая за хранение рёбер графа
struct edge{
	vert* to;
	double weight;
	int visited;
};

//Структура, отвечающая за хранение вершин графа
struct vert{
	char symb;
	std::vector<edge> edges;
};

//Класс-компаратор. Необходим для корректного построения очереди с приоритетом
class comp{
	public:
		bool operator()(edge*& a, edge*& b){
			if(a->weight == b->weight) return a->to->symb > b->to->symb;
			return a->weight > b->weight;
		}
};

std::vector<vert*> path_greedy(vert* cur, vert* finish
										#ifdef DEBUG
										,size_t rec_ln
										#endif
										){
	//Функция поиска пути рекурсивна. 
	//Поэтому если текущее ребро конечное, то завершаем рекурсию и возвращаем результат
	if(cur == finish){
		std::vector<vert*> ret;
		ret.push_back(cur);
		return ret;
	}
	
	//Создаём очередь с приоритетом на основании рёбер графа и класаа-компаратора
	std::priority_queue<edge*, std::vector<edge*>, comp> q;
	for(size_t i = 0; i < cur->edges.size(); ++i)
		if(!cur->edges[i].visited)
			q.push(&cur->edges[i]);

	//Пока очередь не пуста
	while(!q.empty()){
		//Извлекаем из очереди вершину, в которую ведёт ребро
		edge* e = q.top();
		q.pop();
		
		//Отмечаем вершину как посещенную
		e->visited = 1;
		//рекурсивный вызов
		#ifdef DEBUG
		for(size_t i = 0; i < rec_ln; ++i) printf("  ");
		printf("%c -- %.2lf --> %c\n", cur->symb, e->weight, e->to->symb);
		std::vector<vert*> path_r = path_greedy(e->to, finish, rec_ln + 1);
		#else
		std::vector<vert*> path_r = path_greedy(e->to, finish);
		#endif
		//выход из цикла, если найден ответ
		//перед этим будет получена цепочка вершин
		//при завершении рекурсии
		if(path_r.size()){
			path_r.push_back(cur);
			return path_r;
		}
	}
	#ifdef DEBUG
	for(size_t i = 0; i < rec_ln; ++i) printf("  ");
	std::cout << "< no more edges for " << cur->symb << " >\n" ;
	#endif
	return {};
}

int main(){
	char start_ch, finish_ch;
	vert verts['z' - 'a' + 1];
	//инициализируем все вершины нулями
	for(size_t i = 0; i < 'z' - 'a' + 1; i++) verts[i].symb = 0;
	//ввод данных
	scanf("%c %c", &start_ch, &finish_ch);
	vert *start = verts + (start_ch - 'a'), *finish = verts + (finish_ch - 'a');
	start->symb = start_ch;
	finish->symb = finish_ch;

	char from_ch, to_ch; 
	double e_weight;
	while(scanf(" %c %c%lf", &from_ch, &to_ch, &e_weight) == 3){
		vert* from = verts + (from_ch - 'a');
		vert* to = verts + (to_ch - 'a');

		if(!from->symb) 	from->symb = from_ch;
		if(!to->symb)		to->symb = to_ch;

		from->edges.push_back({to, e_weight});
	}
	//первиный вызов функции
	#ifdef DEBUG
	std::cout << "Greedy path search:\n";
	std::vector<vert*> path = path_greedy(start, finish, 0);
	#else
	std::vector<vert*> path = path_greedy(start, finish);
	#endif
	#ifdef DEBUG
	std::cout << "\nPath: ";
	#endif
	//вывод результатов, если ответ найден
	if(path.size()){
		for(size_t i = path.size() - 1;; --i){
			std::cout << path[i]->symb;
			if(i == 0) break;
		}
		std::cout << std::endl;
	}
	//вывод результатов, если ответ не найден
	else
		std::cout << "Path from " << start_ch << " to " << finish_ch << " doesn't exist in this graph.\n";
}