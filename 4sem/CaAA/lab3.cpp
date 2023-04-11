#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>

#define DEBUG

//структура, которая хранит сеть в виде пары матриц смежности
struct graph{
	unsigned source, sink;
	unsigned vert_count;
	int** cap;
	int** flow;
};

//Функция, которая отвечает за вывод остаточной сети
void print_graph(graph* g){
	for(unsigned i = 0; i < 256; ++i)
		for(unsigned j = 0; j < 256; ++j)
			if(g->cap[i][j] > 0)
				std::cout << (char)i << " --> " << (char)j << " cap " << g->cap[i][j] << ", flow " << g->flow[i][j] << "\n";
}

//Итеративная часть алгоритма, ищущая путь и обрабатывающая его
int ford_fulkerson_iter(graph* g, unsigned char* visited){
    //Стэк, который хранит пары значений. Ключевой элемент реализации
    //состоит из пар значений ИсходящаяВершина-пропускная способность ребра 
    std::vector<std::pair<unsigned, int>> stack;
    //добавляем исток
    stack.push_back({g->source, INT_MAX});
    //инициализируем массив родителей для вершин сети (необходимо для восстановления найденного пути)
    unsigned* parents = new unsigned[g->vert_count];

    //Обработка поиском в глубину сети с целью поиска потока для найденного пути 
    while(!stack.empty()){
        //Извлекаем последний элемент стека
        auto a = stack.back();
        stack.pop_back();
        unsigned from = a.first;
        int flow = a.second;
        visited[from] = 1;

        //Если последний элемент стека совпадает со стоком
        //То путь найден
        //Восстанавливаем путь и возвращаем величину потока по этому пути
        //Также установим веса обратных рёбер
        if(from == g->sink){
            #ifdef DEBUG
            std::cout << "Flow amount: " << flow << "\n";
            #endif
            for(unsigned j = from; j != g->source; j = parents[j]){
                g->cap[parents[j]][j] -= flow;
                g->cap[j][parents[j]] += flow;
				g->flow[parents[j]][j] += flow;
				g->flow[j][parents[j]] -= flow;
                #ifdef DEBUG
                std::cout << (char)j << " <-- ";
                #endif
            }
            #ifdef DEBUG
            std::cout << (char)g->source << "\n";
            #endif
            delete[] parents;
            return flow;
        }

        //Извлечённая вершина не оказалась стоком
        //Тогда ищем путь поиском в глубину, проходясь по вершинам графа
        for(unsigned i = 0; i < g->vert_count; ++i){
            //Если текущая вершина ещё не посещена и значение в матрице межности
            //пропускных способностей больше 0, то добавляем в стек новый элемент (пару значений)
            //и обновляем массив родителей
            if(!visited[i] && g->cap[from][i] > 0){
                stack.push_back({i, flow < g->cap[from][i] ? flow : g->cap[from][i]});
                parents[i] = from;
                #ifdef DEBUG
                std::cout << (char)from << " --> " << (char)i << " : " << g->cap[from][i] << "\n";
                #endif
            }
        }
    }
    //очищаем память, задействованную под массив
    delete[] parents;
	return 0;
}

//Внешняя функция, которая многократно вызывает итеративную функцию
int ford_fulkerson(graph* g){
    //Создаём массив булевых значений, который помечает посещённые вершины
	unsigned char* visited = new unsigned char[g->vert_count];
	memset(visited, 0, g->vert_count);
    //Задаём переменные ответственные за поток и максимальный поток
	int total_flow = 0, flow;
    //Вызовы итеративной функции, пока путь из истока в сток не перестанет существовать
	while(flow = ford_fulkerson_iter(g, visited)){
		#ifdef DEBUG
		std::cout << "\nUpdated graph:\n";
		print_graph(g);
		std::cout << std::endl;
		#endif
		memset(visited, 0, g->vert_count);
		total_flow += flow;
	}
    //Очищаем память, задействованную под массив
	delete visited;
	return total_flow;
}

//Структура, хранящая рёбра
struct orig_edge{
	unsigned from, to;
};

//Класс-компаратор
class comp{
    public:
        bool operator()(const orig_edge& e1, const orig_edge& e2){
            if(e1.from < e2.from) return true;
            else if(e1.from > e2.from) return false;
            else return e1.to < e2.to;
        }
};

int main(){
    //Считываем количество рёбер
	unsigned edge_cnt;
    std::cin >> edge_cnt;

    //Инициализируем сеть и заполняем нулями матрицы смежности
    //(делаем это, чтобы не получить каких-нибудь "плохих" значений при дальнейшей работе)
	graph g;
    g.vert_count = 256;
	g.cap = new int* [g.vert_count];
	for(unsigned i = 0; i < g.vert_count; ++i){
		g.cap[i] = new int[g.vert_count];
		memset(g.cap[i], 0, sizeof(int) * g.vert_count);
	}
	g.flow = new int*[g.vert_count];
	for(unsigned i = 0; i < g.vert_count; ++i){
		g.flow[i] = new int[g.vert_count];
		memset(g.flow[i], 0, sizeof(int) * g.vert_count);
	}

    //Получаем исток и сток
	char source, sink;
    std::cin >> source;
	g.source = source;
    std::cin >> sink;
	g.sink = sink;

    //Получаем ребра
    std::vector<orig_edge> edges;
	for(unsigned i = 0; i < edge_cnt; ++i){
		char from, to; 
        int weight;
		scanf(" %c", &from);
		scanf(" %c", &to);
		scanf("%d", &weight);
		g.cap[(unsigned)from][(unsigned)to] = weight;
        //Создаём вектор "оригинальных" рёбер
        orig_edge e = {(unsigned)from, (unsigned)to};
        edges.push_back(e);
	}

    //Вызов алгоритма
	int max_flow = ford_fulkerson(&g);
	#ifdef DEBUG
	std::cout << "final result:\n";
	#endif
    //Вывод результатов и их сортировка
	std::cout << max_flow << "\n";
    std::sort(edges.begin(), edges.end(), comp());
	for(unsigned i = 0; i < edge_cnt; ++i)
		printf("%c %c %d\n", edges[i].from, edges[i].to, g.flow[edges[i].from][edges[i].to] < 0 ? 0 : g.flow[edges[i].from][edges[i].to]);

    //Очистка задействованной памяти
	for(unsigned i = 0; i < g.vert_count; ++i)
		delete g.cap[i];
	delete g.cap;

	for(unsigned i = 0; i < g.vert_count; ++i)
		delete g.flow[i];
	delete g.flow;
}