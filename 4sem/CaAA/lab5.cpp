#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>

#define DEBUG
#define PRINT_SUFFIX_CHAINS
using namespace std;

struct bohr{
	char c = '?';
	size_t index = (size_t)-1;
	bohr* parent = nullptr;

	bohr* child = nullptr;
	bohr* brother = nullptr;

	bohr* suffix = nullptr;
	bohr* dict_suffix = nullptr;
};

//Функция создания конечного автомата (возвращает корень либо пустую строку)
//Описываем узел Бора
bohr* bohr_create(string* dict, size_t dict_ln){
	bohr* root = new bohr();
	root->parent = root;
	
	// Создаём первоначальное дерево
	for(size_t i = 0; i < dict_ln; ++i){
		bohr* prev = root;
		for(const char* it = dict[i].c_str(); *it; ++it){
			bohr* cur = prev->child;
			if(!cur){ // Если ещё нет потомков
				prev->child = new bohr();
				prev->child->parent = prev;
				prev->child->c = *it;
				prev = prev->child;

				next_char:
				if(it[1] == '\0')  // Последний символ С-шной строки, к которой кастанули словарь подстрок
					prev->index = i;
				continue;
			}
			// в противном случае сканируйте все дочерние элементы родительского узла, чтобы предотвратить дублирование префиксов
			while(cur->brother){
				if(cur->c == *it){
					prev = cur;
					goto next_char;
				}
				cur = cur->brother;
			}

			//повторений среди потомков не нашли - добавляем новую дочернюю вершниу
			if(cur->c == *it){
				prev = cur;
				goto next_char;
			}

			cur->brother = new bohr();
			cur->brother->c = *it;
			cur->brother->parent = prev;

			if(it[1] == '\0')
				cur->brother->index = i;
			prev = cur->brother;
		}
	}

	//Создаём суффиксные ссылки
	queue<bohr*> q;
	q.push(root);
	while(!q.empty()){
		bohr* n = q.front();
		q.pop();
		bohr* parent = n->parent;
		//корень не имеет суффикса, поэтому край суффикса указывает на корень
		//(т.Е. узлы на первом уровне обрабатываются прямо сейчас)
		if(parent == root){
			n->suffix = root;
			goto put_children;
		}

		while(1){
			parent = parent->suffix; //узел суффикса
			//просматриваем всех детей у данного узла
			bohr* it = parent->child;
			while(it){
				if(it->c == n->c)
					break;
				it = it->brother;
			}

			if(it){ //если был найден дочерний элемент с соответствующим символом
				n->suffix = it; // это суффикс текущего узла
				break;
			}

			if(parent == root){ // среди дочерних элементов ничего не найдено
				n->suffix = root; // rуффиксом данного узла является корень
				break;
			}
			// дочерний элемент с соответствующим символом не был найден, продолжая движение вверх по дереву...
		}

		put_children:;
		bohr* it = n->child;
		while(it){ //вывести всех детей узла в очередь
			q.push(it);
			it = it->brother;
		}
	}

	// Построение суффиксных ребёр
	q.push(root);
	while(!q.empty()){
		bohr* n = q.front();
		q.pop();
		bohr* cur = n->suffix;

		// Находим следующий узел бора, до которого можно добраться по суффиксным рёбрам
		while(cur != root){
			if(cur->index != (size_t)-1)
				break;
			cur = cur->suffix;
		}

		if(cur != root)
			n->dict_suffix = cur;

		bohr* it = n->child;
		while(it){ // вывести всех детей узла в очередь
			q.push(it);
			it = it->brother;
		}
	}
	return root;
}

//Функция высвобожения памяти под Бор
static void bohr_free(bohr* root){
	bohr* it = root->child;
	while(it){
		bohr* next = it->brother;
		bohr_free(it);
		it = next;
	}
	delete root;
}


//Функция получения подстроки из Бора по вершинам (узлам) и суффиксным ссылкам
char* bohr_getval(bohr* root, bohr* n, char* buf, size_t buf_sz){
	size_t buf_i = buf_sz - 2;
	buf[buf_sz - 1] = '\0';
	
	if(n == root){
		buf[buf_sz - 2] = '?';
		return buf + buf_sz - 2;
	}

	bohr* it = n;
	while(it != root){
		buf[buf_i--] = it->c;
		it = it->parent;
	}

	return buf + buf_i + 1;
}

//Вывод конечного автомата по уровням
void bohr_print(bohr* root){
	queue<bohr*> q;
	q.push(root);
	// Вывод всех узлов
	string lvl_sep = "----------------------------------------------";
	printf("%-10s  %-4s  %-6s  %-6s  %-11s\n", "value", "dict", "parent", "suffix", "dict suffix");
	char cur_lvl_bit = 0;	// указывает текущий уровень первого бита символа бора
	cout << lvl_sep << endl;
	while(!q.empty()){
		bohr* n = q.front();
		q.pop();

		if(!!(n->c & (1 << 7)) != cur_lvl_bit){
			// если уровень узла и текущий уровень не совпадают, мы должны ввести новый уровень
			cur_lvl_bit = !cur_lvl_bit;
			cout << lvl_sep << endl;
		}
		n->c &= ~(1 << 7); // зачищаем бита узла

		char val_buf[4096];
		printf("%-10s", bohr_getval(root, n, val_buf, sizeof(val_buf)));
		if(n->index != (size_t)-1)
			printf("  %-4lu", n->index + 1);
		else
			printf("  --  ");
		printf("  %-6s", n->parent ? bohr_getval(root, n->parent, val_buf, sizeof(val_buf)) : "--");
		printf("  %-6s", n->suffix ? bohr_getval(root, n->suffix, val_buf, sizeof(val_buf)) : "--");
		printf("  %-11s\n", n->dict_suffix ? bohr_getval(root, n->dict_suffix, val_buf, sizeof(val_buf)) : "--");

		bohr* it = n->child;
		while(it){ // вывести всех потомков узла в очередь
			if(!cur_lvl_bit) // устанавливаем бит уровня узла на значение, обратное текущему
				it->c |= (1 << 7);
			q.push(it);
			it = it->brother;
		}
	}
	cout << lvl_sep << endl;
}

//Индивидуализация: функция вывода длиннейшей суффиксной ссылки
void bohr_print_suffix_chains(bohr* root){
	queue<bohr*> q;
	q.push(root);

	bohr* max_suff_ln_node = NULL;		
	size_t max_suff_ln = 0;
	bohr* max_dict_ln_node = NULL;		
	size_t max_dict_ln = 0;

	while(!q.empty()){
		bohr* n = q.front();
		q.pop();
		// Ищем наибольшую суффиксную ссылку
		size_t ln = 1;
		bohr* it = n->suffix;
		while(it != root){
			++ln;
			it = it->suffix;
		}

		if(ln > max_suff_ln){
			max_suff_ln_node = n;
			max_suff_ln = ln;
		}

		// ищем наибольшее ребро до ближайшего суффикса из множества подстрок
		ln = 1;
		it = n->dict_suffix;
		while(it){
			++ln;
			it = it->dict_suffix;
		}

		if(ln > max_dict_ln){
			max_dict_ln_node = n;
			max_dict_ln = ln;
		}

		it = n->child;
		while(it){ // Вывести всех детей узла в очередь
			q.push(it);
			it = it->brother;
		}
	}

	cout << "Longest suffix chain:" << endl;
	char val_buf[4096];
	bohr* it = max_suff_ln_node;
	
	while(1){
		printf(it == max_suff_ln_node ? "%s" : " --> %s", it == root ? "<root>" : bohr_getval(root, it, val_buf, sizeof(val_buf)));
		if(it == root)
			break;
		it = it->suffix;
	}

	cout << "\nLongest dictionary suffix chain:" << endl;
	it = max_dict_ln_node;
	
	while(it){
		printf(it == max_dict_ln_node ? "%s" : " --> %s", bohr_getval(root, it, val_buf, sizeof(val_buf)));
		it = it->dict_suffix;
	}
	cout << endl;
}

//Структура, необходимая для поиска в боре подстрок
struct bohr_search_res{
	size_t texti;
	size_t dicti;
};

//Класс-компаратор
class bohr_res_cmp{
	public:
	bool operator()(const bohr_search_res& r1, const bohr_search_res& r2){
		if(r1.texti > r2.texti) 	return  false;
		else if(r1.texti < r2.texti) 	return true;
		else return r1.dicti < r2.dicti;
	}; 
};

//Функция поиска подстрок в строке при помощи бора
vector<bohr_search_res> bohr_search(string text, string* dict, size_t dict_ln){
	bohr* g = bohr_create(dict, dict_ln);

	#ifdef DEBUG
	cout << "Graph for dictionary " << endl;
	for(size_t i = 0; i < dict_ln; ++i){
		if(i == dict_ln-1) cout << '"' << dict[i] << "\"\n"; 
		else cout << '"' << dict[i] << "\", "; 
	}
	bohr_print(g);

	
	#endif

	#ifdef PRINT_SUFFIX_CHAINS
	cout << endl;
	bohr_print_suffix_chains(g);
	#endif
	
	vector<bohr_search_res> res; 
	bohr* cur_node = g;
	#ifdef DEBUG
	printf( "\nSearching in string \"%s\":\n"
		"%-50s %-10s %-7s\n",
		text.c_str(), "position in string", "node", "matches");
	#endif
	for(const char* text_it = text.c_str(); *text_it; ++text_it){
		// пытаемся расширить текущий узел через потомков
		bohr* it = cur_node->child;
		while(it){
			if(it->c == *text_it)
				break;
			it = it->brother;
		}
		
		bohr* cur_suf = cur_node->suffix;
		
		if(it){
			cur_node = it;
			goto suffix_ext_end;
		}
		// пытаемся расширить текущий узел через суффикс, через дочерний суффикс суффикса и так далее
		
		while(1){
			it = cur_suf->child;
			while(it){
				if(it->c == *text_it)
					break;
				it = it->brother;
			}
			if(it){
				cur_node = it;
				goto suffix_ext_end;
			}
			if(cur_suf == g) // просмотрел корень и ничего не получил? пора уходить
				break;
			cur_suf = cur_suf->suffix;
		}

		cur_node = g;

		suffix_ext_end:;
		#ifdef DEBUG
		char val_buf[4096];
		int first_match_print = 1;
		for(const char* i = text.c_str(); *i; ++i){
			if(i == text_it) printf("\x1b[1m\x1b[31m");
			putchar(*i);
			if(i == text_it) printf("\x1b[0m");
		}
		for(size_t i = text.length(); i < 50; ++i) putchar(' ');
		printf(" %-10s ", bohr_getval(g, cur_node, val_buf, sizeof(val_buf)));
		#endif
		if(cur_node->index != (size_t)-1){ // добавить текущий узел в список совпадений
			#ifdef DEBUG
			printf(first_match_print ? "\"%s\"" : ", \"%s\"", bohr_getval(g, cur_node, val_buf, sizeof(val_buf)));
			first_match_print = 0;
			#endif
			res.push_back({text_it - text.c_str() + 1 - dict[cur_node->index].length(), cur_node->index});
		}

		it = cur_node->dict_suffix;
		while(it){ // добавляем все суффиксы ребёр до ближайшего суффикса из множества подстрок текущего узла в список совпадений 
			#ifdef DEBUG
			printf(first_match_print ? "\"%s\"" : ", \"%s\"", bohr_getval(g, it, val_buf, sizeof(val_buf)));
			first_match_print = 0;
			#endif
			res.push_back({text_it - text.c_str() + 1 - dict[it->index].length(), it->index});
			it = it->dict_suffix;
		}
		#ifdef DEBUG
		cout << endl;
		#endif
	}

	#ifdef DEBUG
	cout << endl;
	#endif
	sort(res.begin(), res.end(), bohr_res_cmp());
	bohr_free(g);
	return res;
}

int main(){
	size_t n = 0;
	string text_in;
	std::getline(cin, text_in); 
	size_t dict_ln;	
	cin >> dict_ln;	
	
	string* dict_in = new string[dict_ln];
	cin.ignore();
	for(size_t i = 0; i < dict_ln; ++i){
		std::getline(cin, dict_in[i]);
	}

	vector<bohr_search_res> res = bohr_search(text_in, dict_in, dict_ln);
	for(auto it = res.begin(); it != res.end(); ++it)
		cout << it->texti + 1 << " " << it->dicti + 1 << endl;
}