#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#define DEBUG 1

std::vector<int> get_prefix (std::string s){
	int n = (int) s.length();
	std::vector<int> p_i (n); //в i-м элементе количество совпавших символов
	
    #if DEBUG == 1
    std::cout << "Finding prefix-function for substring:" << s << "\n";
    #endif
	for (int i=1; i<n; ++i){ 
		//ищем префикс, который можно расширить
        int j = p_i[i-1]; //длина предыдущего префикса
		#if DEBUG == 1
        std::cout << "index j:" << j << "\n";
		std::cout << "index i:" << i << "\n";
        #endif
        //при помощи цикла проверяем, что нельзя расширить префикс
		//префикс нельзя расширить, пока длина предыдущего префикса не стала больше 0 и 
        //текущий проверяемый префикс не стал равен префиксу текущей длины
        //поэтому берём длину меньшего префикса
        while (j > 0 && s[i] != s[j]) j = p_i[j-1];
		//если можем расширить префикс, то расширяем его
        if (s[i] == s[j]) ++j;
		//так как найдено совпадение, то записываем найденное значение в префикс
        p_i[i] = j; 
	}

    #if DEBUG == 1
	std::cout << "Prefix-function contains: "; 
	for (int i = 0; i < p_i.size(); i++){
		std::cout << p_i[i] << " ";}
	std::cout << "\n";
    #endif 
	return p_i;
}

void debug(std::string text, std::string pattern, int i, int j, std::vector<int> P){
	for(int k=0; k<i; k++)std::cout << " "; std::cout << "i" << std::endl;
	for(int k=0; k<i; k++)std::cout << " "; std::cout << "⌄" << std::endl;
	std::cout << text << std::endl;
	std::cout << pattern << std::endl;
	for(int k=0; k<j; k++)std::cout << " "; std::cout << "⌃" << std::endl;
	for(int k=0; k<j; k++)std::cout << " "; std::cout << "j" << std::endl;
}

std::vector<int> find(std::string text, std::string pattern){
	int i=0, j=0, n = text.length(), m=pattern.length();
	std::vector<int> P = get_prefix(pattern);
	std::vector<int> res;
    while(i<n){
        //символы строки и образа совпадают, значит увеличиваем индексы
        //текущего символа строки и текущего символа образа
        if(pattern[j]==text[i]){
            i++;
            j++;
        }

        //индекс текущего символа образа достиг конца образа, значит, подстрока найдена
        //заносим её в результат
        if (j == m){
			res.push_back(i-m); 
			#if DEBUG == 1
				std::cout << "Find new entry " << i-m << std::endl;
            	std::cout << "Going to " << P[j-1] << std::endl;	
            #endif 											
            j = P[j - 1]; 
        }

        //в строке обнаружено несовпадение с подстрокой
        else if (i < n && pattern[j] != text[i]){
            //если текущий символ строки не совпадает с текущим символом строки
            //сдвигаем текущий символ строки
            if (j == 0) i++;
            //если текущий символ подстроки не совпадает с текушим символом строки
            //и текущий символ подстроки не первый, то сдвигаем текущий символ подстроки
            else{
                #if DEBUG == 1
					std::cout << "Going to " << P[j-1] << std::endl;
				#endif
				j = P[j - 1];
			}
        }
		#if DEBUG == 1
			debug(text, pattern, i, j, P);
		#endif
    }
	return res;
}

int main(){
	std::string text, pattern;
	std::cin >> pattern >> text;
	std::vector<int> res;
	res = find(text, pattern);	

	if(res.empty()){
		std::cout << "-1";
		std::cout << std::endl;
	}
	
	for(int i=0;i<res.size();i++){
		if(i==res.size()-1) std::cout << res.at(i);
		else std::cout << res.at(i) << ',';
	}
	std::cout << "\n";
    return 0;
}