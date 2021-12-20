#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>



int comp(const void* a, const void* b){
        int num1, num2;
        sscanf(*((char**)a), "%d", &num1);
        sscanf(*((char**)b), "%d", &num2);
        if(num1 > num2) return 1;
        if(num1 == num2) return 0;
        if(num1 < num2) return -1;
}

void find_dir(char* dir_path, char** tmp, int* i){ //В tmp вписываем все строки для сортировки, i отвечает за номер элемента массива в tmp 
        FILE *f;
        DIR *dir = opendir(dir_path);
        if(dir){
            struct dirent *de;
            while (de = readdir(dir)){
                    //Строки для смены адреса директории
                    char* adress = malloc((strlen(dir_path)+strlen(de->d_name)+2)*sizeof(char));
                    strcpy(adress, dir_path);
                    strcat(adress, de->d_name);
                    if(de->d_type == DT_REG){
                            if(f = fopen(adress, "r")){       
                                    tmp[*i] = malloc(32*sizeof(char));
                                    if(!fgets(tmp[*i], 32*sizeof(char), f)){
                                            continue;
                                    }
                                    (*i)++;
                                    fclose(f);
                            }
                    }
                    else if(de->d_type == DT_DIR){
                            if(!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")) //Проверяем, не оказались ли мы в предыдущей директории
                            {
                                    free(adress);
                                    continue;
                            }
                            char *new_dir_path = malloc((strlen(dir_path)+strlen(de->d_name)+2)*sizeof(char));//Переходим в новую директорию, так как не нашли файл для считывание
                            strcpy(new_dir_path, dir_path);
                            strcat(new_dir_path, de->d_name);
                            strcat(new_dir_path, "/");
                            find_dir(new_dir_path, tmp, i);
                            free(new_dir_path);
                    }
                    free(adress);
            }
        closedir(dir);
        }
}

int main(){
        char* dir_path = "./root/";
        char* tmp[8192];
        int i = 0;

        find_dir(dir_path, tmp, &i);
        qsort(tmp, i, sizeof(char*), comp);

        FILE *f;
        f = fopen("./result.txt", "w");
        int j;
        for(j = 0; j < i; j++){
//              fprintf(stderr, "%p\n", tmp[j]);
               fprintf(f, "%s\n", tmp[j]);
        }
        fclose(f);
}
