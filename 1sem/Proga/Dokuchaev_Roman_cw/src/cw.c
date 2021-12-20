#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define sent 10

char **input(size_t *size_of_text)
{
	//Задаём необходимые для считывания переменные
	char **text;
	char *sentence; //Буффер
	int a = 0;
	int size_sentence = 1;
	size_t text_size = 0;			 //Переменные отвечают за размер отдельного предложения и текста
	sentence = malloc(sizeof(char)); //Выделение памяти под первый символ предложения
	text = malloc(sizeof(char *));	 //Выделение памяти под первое предложение текста
	//Непосредственно цикл для считывания предложения
	sentence[a] = getchar();
	while (sentence[a] != '\n')
	{
		//Условие завершения записи предложения
		if (sentence[a] == '.')
		{
			text_size++;
			text = (char **)realloc(text, text_size * sizeof(char *));
			text[text_size - 1] = malloc((a + 2) * sizeof(char));
			memcpy(text[text_size - 1], sentence, (a + 2) * sizeof(char));
			text[text_size - 1][a + 1] = '\0';
			a = 0;
			sentence[a] = getchar();
			continue;
		}
		a++;
		//Условие для увеличения памяти
		if (a >= (size_sentence - 2))
		{
			size_sentence += sent;
			char* temp;
			temp = (char *)realloc(sentence, size_sentence * sizeof(char));
			if (temp == NULL)
			{
				for (int j = 0; j < text_size; j++)
				{
					free(text[j]);
					text[j] = NULL;
				}
				free(text);
				text = NULL;
				return text;
			}
			sentence = temp;
		}
		sentence[a] = getchar();
	}
	free(sentence);
	*size_of_text = text_size;
	return text;
}

//Удаление повторяющихся предложений.
char **delete_duplicate(char **text, size_t *text_size)
{
	//Проходимся по тексту по каждому предложению в отдельности. Записываем пронумерованное предложение в временную переменную
	for (int a = 0; a < (*text_size - 1); a++)
	{
		//Записываем предложение для сравнения в другую переменную
		for (int b = a + 1; b < *text_size; b++)
		{
			//Сравниваем без учёта регистра повторяющиеся предложения и удаляем их
			if (strcasecmp(text[a], text[b]) == 0)
			{
				free(text[b]);
				memmove(&text[b], &text[b + 1], (*(text_size)-b - 1) * sizeof(char *));
				*text_size -= 1;
				b--;
			}
		}
	}
	text = realloc(text, *text_size * sizeof(char *));
	return text;
}

//Функция по поиску и подсчёту цифр в исходном тексте
int *is_digit(char **text, size_t text_size)
{
	char *sentence;
	//Создаём динамический массив с цифрами текста, в котором каждый элемент по порядку соответствует своей цифре (0-ой элемент - 0, 1-ый - 1 и тюдю)
	int *arr = malloc(10 * sizeof(int));
	for (int i = 0; i < 10; i++)
	{
		arr[i] = 0;
	}
	for (int i = 0; i < text_size; i++)
	{
		sentence = text[i];
		for (int j = 0; j < strlen(text[i]); j++)
		{
			if (isdigit(sentence[j]))
			{
				arr[sentence[j] - '0']++;
			}
		}
	}
	return arr;
}

//Функция вывода предложений текста в обратном порядке
char **reverse_order(char **text, size_t text_size)
{
	char *begin, *end; //Указатели на начало и
	for (int i = 0; i < text_size; i++)
	{
		begin = text[i];
		end = text[i] + strlen(text[i]) - 2;
		while (begin < end)
		{
			if (*begin != ' ' && *end != ' ' && *begin != ',' && *end != ',')
			{
				char c = *begin;
				*begin = *end;
				*end = c;
			}
			begin++;
			end--;
		}
	}
	return text;
}

//Функция удаления предложений со словом physics
char **delete_physics(char **text, size_t *text_size)
{
	for (int a = 0; a < *text_size; a++)
	{
		if (strstr(text[a], "physics"))
		{
			memmove(&text[a], &text[a + 1], (*(text_size)-a - 1) * sizeof(char *));
			*text_size -= 1;
		}
	}
	text = realloc(text, *text_size * sizeof(char *));
	return text;
}

//Функция для сравнения строк
int function_for_sort_sentence(const void *arg1, const void *arg2)
{
	char *sentence1 = *((char **)arg1), *sentence2 = *((char **)arg2);
	int flag = 0;
	char *word_start;
	char *current_symbol;
	int count1 = 0, count2 = 0;
	//Считаем количество слов из 3 букв в первом предложении
	for (current_symbol = sentence1; *current_symbol != '\0'; current_symbol++)
	{
		if (*current_symbol != ' ' && *current_symbol != ',' && *current_symbol != '.' && flag == 0)
		{
			flag = 1; //Мы внутри слова
			word_start = current_symbol;
		}
		else if ((*current_symbol == ' ' || *current_symbol == ',' || *current_symbol == '.') && flag == 1)
		{
			flag = 0; //Наткнулись на конец слова
			if ((current_symbol - word_start) == 3)
			{
				count1++;
			}
		}
	}
	//Считаем количество слов из 3 букв во втором предложении
	for (current_symbol = sentence2; *current_symbol != '\0'; current_symbol++)
	{
		if (*current_symbol != ' ' && *current_symbol != ',' && *current_symbol != '.' && flag == 0)
		{
			flag = 1; //Мы внутри слова
			word_start = current_symbol;
		}
		else if ((*current_symbol == ' ' || *current_symbol == ',' || *current_symbol == '.') && flag == 1)
		{
			flag = 0; //Наткнулись на конец слова
			if ((current_symbol - word_start) == 3)
			{
				count2++;
			}
		}
	}
	if (count1 > count2)
	{
		return 1;
	}
	else if (count1 < count2)
	{
		return -1;
	}
	else
		return 0;
}

//Функция, сортирующая предложения в зависимости от количества слов из 3 букв
char **sorting_function(char **text, size_t text_size)
{
	qsort(text, text_size, sizeof(char *), function_for_sort_sentence);
	return text;
}

//Функция вывода полученного в результате обработки текста
void output(char **text, size_t text_size)
{
	for (int a = 0; a < text_size; a++)
	{
		printf("%s", text[a]);
	}
	printf("\n");
}

//Функция с защиты: удаление повторяющихся слов
char* remove_duplicate_words(char* sentence){
	char* copy_sentence = malloc(sizeof(char) * (strlen(sentence) + 1));
	int flag = 0;
	char** arr = NULL; //
	size_t size_arr = 0;	
	char* cur, *copy_cur;
	char* word_start;
	for(cur = sentence, copy_cur = copy_sentence; *cur != '\0'; cur++){
		if(flag == 0){
			*copy_cur = *cur;
			copy_cur++;
			if (cur[1] != ' ' && cur[1] != ',' && cur[1] != '.'){
				flag = 1;
				word_start = cur + 1;
			}
		}
		else if (flag == 1){
			if (cur[1] == ' ' || cur[1] == ',' || cur[1] == '.'){
				flag = 0;
				int word_found = 0;
				for(size_t i = 0; i < size_arr; i++){
					if (!strncmp(arr[i], word_start, (cur - word_start + 1))){
						word_found = 1;
						break;
					}
				}
				if (!word_found){
					size_arr++;
			       		char** temp = realloc(arr, sizeof(char*) * size_arr);
			 		if (temp == NULL){
						if (arr != NULL) 
							free(arr);
						return NULL;
					}
					arr = temp;
					arr[size_arr - 1] = malloc(sizeof(char) * (cur - word_start + 1));
					memcpy(arr[size_arr - 1], word_start, sizeof(char)*(cur - word_start + 1));
					memcpy(copy_cur, word_start, sizeof(char) * (cur - word_start + 1));
					copy_cur += (cur - word_start + 1);
				}
			}
		}
	}
	*copy_cur = '\0';
	free(arr);
	return copy_sentence;
}



//Вывод массива всех слов
char** array_of_words(char** text, size_t text_size, size_t* word_size_ptr){
	char** words = NULL;
	size_t words_size = 0;
	int flag = 0;
	char* word_start;
	for(size_t i = 0; i < text_size; i++){
		for(char* cur = text[i]; *cur != '\0'; cur++){
			if (flag == 0 && *cur != ' ' && *cur != '.' && *cur != ','){
				flag = 1;
				word_start = cur;
			}
			else if(flag == 1 && (*cur == ' ' || *cur == ',' || *cur == '.')){
				flag = 0;
				int word_found = 0;
				for(size_t j = 0; j < words_size; j++){
					if ((cur - word_start) == strlen(words[j]) && !strncmp(words[j], word_start, (cur - word_start))){
						word_found = 1;
						break;
					}
				}
				if (!word_found){
					words_size++;
					char** temp = realloc(words, words_size * sizeof(char*));
					if (temp == NULL){
						if (words != NULL){
							free(words);
						}
						return NULL;
					}
					words = temp;
					words[words_size - 1] = malloc(sizeof(char) * (cur - word_start + 1));
					memcpy(words[words_size - 1], word_start, sizeof(char)*(cur - word_start));
					words[words_size - 1][cur - word_start] = '\0';
				}
			}
		}
	}
	*word_size_ptr = words_size;
	return words;
}

//Удаление слов, которые встречаются от 3 до 5 раз
void search_and_destroy(char** text, size_t text_size){
        char** words = NULL;
	size_t* number_of_rep = NULL;
        size_t words_size = 0;
        int flag = 0;
        char* word_start;
        for(size_t i = 0; i < text_size; i++){
                for(char* cur = text[i]; *cur != '\0'; cur++){
                        if (flag == 0 && *cur != ' ' && *cur != '.' && *cur != ','){
                                flag = 1;
                                word_start = cur;
                        }
                        else if(flag == 1 && (*cur == ' ' || *cur == ',' || *cur == '.')){
                                flag = 0;
                                int word_found = 0;
				size_t word_index = 0;
                                for(size_t j = 0; j < words_size; j++){
                                        if ((cur - word_start) == strlen(words[j]) && !strncmp(words[j], word_start, (cur - word_start))){
                                                word_found = 1;
						word_index = j;
                                                break;
                                        }
                                }
                                if (!word_found){
                                        words_size++;
                                        char** temp = realloc(words, words_size * sizeof(char*));
                                        if (temp == NULL){
                                                if (words != NULL){
                                                        free(words);
                                                }
                                                return;
                                        }
                                        words = temp;
                                        words[words_size - 1] = malloc(sizeof(char) * (cur - word_start + 1));
                                        memcpy(words[words_size - 1], word_start, sizeof(char)*(cur - word_start));
                                        words[words_size - 1][cur - word_start] = '\0';
					size_t* temp2 = realloc(number_of_rep, sizeof(size_t) * words_size);
					if(temp2 == NULL){
						if(number_of_rep != NULL){
							free(number_of_rep);
						}
						return;
					}
					number_of_rep = temp2;
					number_of_rep[words_size - 1] = 1;
                                }
				else{
					number_of_rep[word_index] ++;
				}
                        }
                }
        }

	flag = 0;
	for(size_t i = 0; i < text_size; i++){
		for(char* cur = text[i]; *cur != '\0'; cur++){
			if(flag == 0 && *cur != ' ' && *cur != ',' && *cur != '.'){
				flag = 1;
				word_start = cur;
			}
			else if(flag == 1 && (*cur == ' ' || *cur == ',' || *cur == '.')){
				flag = 0;
				int word_found = 0;
                                size_t word_index = 0;
                                for(size_t j = 0; j < words_size; j++){
                                        if ((cur - word_start) == strlen(words[j]) && !strncmp(words[j], word_start, (cur - word_start))){
                                                word_found = 1;
                                                word_index = j;
                                                break;
                                        }
                                }
				if(word_found && number_of_rep[word_index] >= 3 && number_of_rep[word_index] <= 5){
					memmove(word_start, cur, ((text[i] + strlen(text[i]) - cur) * sizeof(char)));
					text[i][strlen(text[i])-(cur-word_start)] = '\0';
					cur = word_start;
				}
			}
		}
	}
}

//Удаление самого часто встречаемого слова
void delete_the_repeate(char** text, size_t text_size){
	char** words = NULL;
        size_t* number_of_rep = NULL;
        size_t words_size = 0;
        int flag = 0;
        char* word_start;
        for(size_t i = 0; i < text_size; i++){
                for(char* cur = text[i]; *cur != '\0'; cur++){
                        if (flag == 0 && *cur != ' ' && *cur != '.' && *cur != ','){
                                flag = 1;
                                word_start = cur;
                        }
                        else if(flag == 1 && (*cur == ' ' || *cur == ',' || *cur == '.')){
                                flag = 0;
                                int word_found = 0;
                                size_t word_index = 0;
                                for(size_t j = 0; j < words_size; j++){
                                        if ((cur - word_start) == strlen(words[j]) && !strncmp(words[j], word_start, (cur - word_start))){
                                                word_found = 1;
                                                word_index = j;
                                                break;
                                        }
                                }
                                if (!word_found){
                                        words_size++;
                                        char** temp = realloc(words, words_size * sizeof(char*));
                                        if (temp == NULL){
                                                if (words != NULL){
                                                        free(words);
                                                }
                                                return;
                                        }
                                        words = temp;
                                        words[words_size - 1] = malloc(sizeof(char) * (cur - word_start + 1));
                                        memcpy(words[words_size - 1], word_start, sizeof(char)*(cur - word_start));
                                        words[words_size - 1][cur - word_start] = '\0';
                                        size_t* temp2 = realloc(number_of_rep, sizeof(size_t) * words_size);
                                        if(temp2 == NULL){
                                                if(number_of_rep != NULL){
                                                        free(number_of_rep);
                                                }
                                                return;
                                        }
                                        number_of_rep = temp2;
                                        number_of_rep[words_size - 1] = 1;
                                }
                                else{
                                        number_of_rep[word_index] ++;
                                }
                        }
                }
        }

        flag = 0;
	char* most_rep;
	size_t freq = 0;
	for(size_t i = 0; i < words_size; i++){
		if (number_of_rep[i] > freq){
			freq = number_of_rep[i];
			most_rep = words[i];
		}
	}
        for(size_t i = 0; i < text_size; i++){
                for(char* cur = text[i]; *cur != '\0'; cur++){
                        if(flag == 0 && *cur != ' ' && *cur != ',' && *cur != '.'){
                                flag = 1;
                                word_start = cur;
                        }
                        else if(flag == 1 && (*cur == ' ' || *cur == ',' || *cur == '.')){
                                flag = 0;
                                if(strlen(most_rep) == (cur - word_start) && !strncmp(most_rep, word_start, (cur-word_start))){
					memmove(word_start, cur, ((text[i] + strlen(text[i]) - cur) * sizeof(char)));
					text[i][strlen(text[i])-(cur-word_start)] = '\0';
					cur = word_start;
                                }
                        }
                }
        }
}

//Главный испольняемый файл
int main()
{
	int key;
	char **text;
	size_t text_size;
	printf("Введите текст.\n");
	text = input(&text_size);
	if (text == NULL)
	{
		printf("Мало памяти!\n");
		return 1;
	}
	text = delete_duplicate(text, &text_size);
	printf(
		"Выберите одно из следующих доступных действий:\n"
		"Введите 1, чтобы посчитать количество всех цифр в тексте и вывести их частоту;\n"
		"Введите 2, чтобы вывести предложения текста в обратном порядке буз учёта пробелов и знаков препинания;\n"
		"Введите 3, чтобы удалить все предложения, включающие physics;\n"
		"Введите 4, чтобы отсортировать предложения текста по словам из трех символов;\n"
		"Введите 0, чтобы завершить выполнение программы.\n");
	while (1)
	{
		key = getchar();
		switch (key)
		{
		case '0':
			printf("Выход из программы\n");
			return 0;
		case '1':
		{
			int *res = is_digit(text, text_size);
			for (int i = 0; i < 10; i++)
			{
				printf("%d:%d\t", i, res[i]);
			}
			printf("\n");
			free(res);
			break;
		}
		case '2':
			text = reverse_order(text, text_size);
			output(text, text_size);
			break;
		case '3':
			text = delete_physics(text, &text_size);
			output(text, text_size);
			break;
		case '4':
			text = sorting_function(text, text_size);
			output(text, text_size);
			break;
		case '5':
			for(size_t i = 0; i < text_size; i++)
			       text[i] = remove_duplicate_words(text[i]); 	
			output(text, text_size);
			break;
		case '6':
		{
			size_t words_size;
			char** words = array_of_words(text, text_size, &words_size);
			for(size_t i = 0; i < words_size; i++){
				printf("%s\t", words[i]);
			}
			printf("\n");
			free(words);
			break;
		}
		case '7':
		{
			search_and_destroy(text, text_size);
			output(text, text_size);
			break;
		}
		case '8':
		{
			delete_the_repeate(text, text_size);
			output(text, text_size);
			break;
		}
		default:
			printf("Такая операция неизвестна. Выберите одно из предложенных значений.\n");
			break;
		}
		getchar();
	}
	for (int j = 0; j < text_size; j++)
	{
		free(text[j]);
	}
	free(text);
	return 0;
}
