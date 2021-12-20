#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

// Описание структуры MusicalComposition
typedef struct MusicalComposition{
	char* name;
	char* author;
	int year;
	struct MusicalComposition* next;
	struct MusicalComposition* prev;
} MusicalComposition;

// Создание структуры MusicalComposition
struct MusicalComposition* createMusicalComposition(char* name, char* author,int year){
	struct MusicalComposition* composition = malloc(sizeof(struct MusicalComposition));
	composition->name = name;
	composition->author = author;
	composition->year = year;
	composition->next = NULL;
	composition->prev = NULL;
	return composition;
}

// Функции для работы со списком MusicalComposition
struct MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
	struct MusicalComposition* list = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
	struct MusicalComposition* temp = list;
	temp->prev = NULL;
	for(int i=1; i<n; i++){
		temp->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
		temp->next->prev = temp;
		temp = temp->next;
	}
	return list;
}

void push(struct MusicalComposition* head, struct MusicalComposition* element){
	struct MusicalComposition* temp = head;
	while(temp->next){
		temp = temp->next;
	}
	temp->next = element;
}

void removeEl(struct MusicalComposition* head, char* name_for_remove){
	struct MusicalComposition* temp = head;
	struct MusicalComposition* list = head;
	while(temp){
		if(!strcmp(name_for_remove, temp->name)){
			list->next = temp->next;
			temp->next->prev = list;
			free(temp);
			break;
		}
		list = temp;
		temp = temp->next;
	}
}

int count(struct MusicalComposition* head){
	struct MusicalComposition* temp = head;
	int i = 0; 
	while(temp){
		i++;
		temp = temp->next;
	}
	return i;
}

void print_names(struct MusicalComposition* head){
	struct MusicalComposition* temp = head;
	while(temp){
		printf("%s\n", temp->name);
		temp = temp->next;
	}
}

int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n"))=0;
        (*strstr(author,"\n"))=0;

        names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);
    }
    struct MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    struct MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(head, element_for_push);

    k = count(head);
    printf("%d\n", k);

    removeEl(head, name_for_remove); 
    print_names(head);

    k = count(head);
    printf("%d\n", k);

    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;

}
