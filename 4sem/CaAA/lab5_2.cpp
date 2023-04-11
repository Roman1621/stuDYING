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

bohr* bohr_create(vector<string> dict){
	bohr* root = new bohr();
	root->parent = root;

	for(size_t i = 0; i < dict.size(); ++i){
		bohr* prev = root;
		for(const char* it = dict[i].c_str(); *it; ++it){
			bohr* cur = prev->child;
			if(!cur){
				prev->child = new bohr();
				prev->child->parent = prev;
				prev->child->c = *it;
				prev = prev->child;

				next_char:
				if(it[1] == '\0')
					prev->index = i;
				continue;
			}
			while(cur->brother){
				if(cur->c == *it){
					prev = cur;
					goto next_char;
				}
				cur = cur->brother;
			}

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

	queue<bohr*> q;
	q.push(root);
	while(!q.empty()){
		bohr* n = q.front();
		q.pop();
		bohr* parent = n->parent;
		if(parent == root){
			n->suffix = root;
			goto put_children;
		}

		while(1){
			parent = parent->suffix;
			bohr* it = parent->child;
			while(it){
				if(it->c == n->c)
					break;
				it = it->brother;
			}

			if(it){
				n->suffix = it;
				break;
			}

			if(parent == root){
				n->suffix = root;
				break;
			}
		}

		put_children:;
		bohr* it = n->child;
		while(it){
			q.push(it);
			it = it->brother;
		}
	}

	q.push(root);
	while(!q.empty()){
		bohr* n = q.front();
		q.pop();
		bohr* cur = n->suffix;

		while(cur != root){
			if(cur->index != (size_t)-1)
				break;
			cur = cur->suffix;
		}

		if(cur != root)
			n->dict_suffix = cur;

		bohr* it = n->child;
		while(it){
			q.push(it);
			it = it->brother;
		}
	}
	return root;
}

static void bohr_free(bohr* root){
	bohr* it = root->child;
	while(it){
		bohr* next = it->brother;
		bohr_free(it);
		it = next;
	}
	delete root;
}

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

void bohr_print(bohr* root){
	queue<bohr*> q;
	q.push(root);
	string lvl_sep = "----------------------------------------------";
	printf("%-10s  %-4s  %-6s  %-6s  %-11s\n", "value", "dict", "parent", "suffix", "dict suffix");
	char cur_lvl_bit = 0;
	cout << lvl_sep << "\n";
	while(!q.empty()){
		bohr* n = q.front();
		q.pop();

		if(!!(n->c & (1 << 7)) != cur_lvl_bit){
			cur_lvl_bit = !cur_lvl_bit;
			cout << lvl_sep << "\n";
		}
		n->c &= ~(1 << 7);

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
		while(it){
			if(!cur_lvl_bit)
				it->c |= (1 << 7);
			q.push(it);
			it = it->brother;
		}
	}
	cout << lvl_sep << "\n";
}

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
		while(it){
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


struct bohr_search_res{
	size_t texti;
	size_t dicti;
};

class bohr_res_cmp{
	public:
	bool operator()(const bohr_search_res& r1, const bohr_search_res& r2){
		if(r1.texti > r2.texti) 	return  false;
		else if(r1.texti < r2.texti) 	return true;
		else return r1.dicti < r2.dicti;
	}; 
};

vector<bohr_search_res> bohr_search(string text, vector<string> dict){
	bohr* g = bohr_create(dict);

	#ifdef DEBUG
	cout << "Graph for dictionary " << endl;
	for(size_t i = 0; i < dict.size(); ++i){
		if(i == dict.size()-1) cout << '"' << dict[i] << "\"\n"; 
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
			if(cur_suf == g)
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
		if(cur_node->index != (size_t)-1){
			#ifdef DEBUG
			printf(first_match_print ? "\"%s\"" : ", \"%s\"", bohr_getval(g, cur_node, val_buf, sizeof(val_buf)));
			first_match_print = 0;
			#endif
			res.push_back({text_it - text.c_str() + 1 - dict[cur_node->index].length(), cur_node->index});
		}

		it = cur_node->dict_suffix;
		while(it){
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
	string text_in;		
    std::getline(cin, text_in);
	string template_in;	
    std::getline(cin, template_in); 	
	char wildcard;
    cin >> wildcard;
    
    //Разделяем исходный текст на части между постановочными знаками
	vector<string> dict_in;
	vector<size_t> dict_pos_in;
	size_t text_ln = text_in.length();

	size_t template_ln = template_in.length();
	long long last_wc_pos = -1;
	for(size_t i = 0; i <= template_ln; ++i){
		if((template_in[i] == wildcard || template_in[i] == '\0') && (i != 0 && template_in[i-1] != wildcard)){
            //Записываем часть и её положение в тексте
            dict_in.push_back(template_in.substr(last_wc_pos+1, i-last_wc_pos-1));
			dict_pos_in.push_back(last_wc_pos + 1);
		}

		if(template_in[i] == wildcard)
			last_wc_pos = i;
	}

	#ifdef DEBUG
	cout << "template slices: " << endl;
	for(size_t i = 0; i < dict_in.size(); ++i)
		printf(i == 0 ? "(%lu: \"%s\")" : ", (%lu: \"%s\")", dict_pos_in[i], dict_in[i].c_str());
	cout << endl;
	#endif

	vector<bohr_search_res> res = bohr_search(text_in, dict_in);

    //первый символ, который не является подстановочным знаком, - смещение для каждого индекса соответствия
	size_t first_nonwc_pos = 0;
	for(size_t i = 0; i < template_ln; ++i)
		if(template_in[i] != wildcard){
			first_nonwc_pos = i;
			break;
		}
	for(auto it = res.begin(); it != res.end(); ++it){
		#ifdef DEBUG
		cout << "Probing from index " << it->texti << endl;
		#endif
		size_t match_i = 0;
		auto jt = it; 
        for(; jt != res.end(); ++jt){
			if(jt->texti - it->texti + first_nonwc_pos > dict_pos_in[match_i])
				break; // если текстовый индекс соответствия превысил длину шаблона, то переходим к следующему
            //если позиции индекса соответствия и позиция текущей части текста совпадает
			else if(jt->texti - it->texti + first_nonwc_pos == dict_pos_in[match_i]){
				char rem = text_in[jt->texti + dict_in[jt->dicti].length()];
				text_in[jt->texti + dict_in[jt->dicti].length()] = '\0';
                //часть и соответствие не совпали, поэтому пропускаем
				if(strcmp(text_in.c_str() + jt->texti, dict_in[match_i].c_str())){
					text_in[jt->texti + dict_in[jt->dicti].length()] = rem;
					continue;
				}
				text_in[jt->texti + dict_in[jt->dicti].length()] = rem;

				#ifdef DEBUG
				cout << "match #" << match_i << ": " << dict_pos_in[match_i] << "<-- " << (jt->texti - it->texti + first_nonwc_pos) << endl;
				#endif
				++match_i; //иначе есть совпадение, переходим к следующему индексу в искомой подстроке
			}
			no_fitting_dict_entry:;
		}
        //нашли непрерывные совпадения подстроки с текстом
		if(match_i == dict_in.size() && it->texti + template_ln - first_nonwc_pos <= text_ln && it->texti >= first_nonwc_pos){
			#ifdef DEBUG
			cout << "found a complete match: " << endl;
			#endif
			cout << (it->texti - first_nonwc_pos + 1) << endl;
		}
		#ifdef DEBUG
		cout << endl;
		#endif
	}
}