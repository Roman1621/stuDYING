#include <iostream>
#include <string.h>
#include <math.h>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits.h>

struct Shannon_Fano{
    int data;
    unsigned int length;
    bool operator==(Shannon_Fano &data){
        return this->data == data.data && this->length == data.length;
    }
};

class Symbol_comp{
    public:
        bool operator()(std::pair<char, unsigned int>& p1, std::pair<char, unsigned int>& p2){
            return p1 > p2;
        }
};

std::ostream& operator<<(std::ostream& out, Shannon_Fano& data){ 
    for(unsigned int i = 0; i < data.length; i++){
        out << ((data.data & (1 << (data.length - 1 - i))) >> (data.length - 1 - i));
    }
    return out;
}



void Shannon_Fano_Table_r(std::vector<std::pair<char, unsigned int>>& symbols, std::map<char, Shannon_Fano>& table, int l, int r);

std::map<char, Shannon_Fano> Shannon_Fano_Table(std::string text){
    unsigned int CharWeight[256];
    for (int i = 0; i < 256; i++){
        CharWeight[i] = 0;
    }
    for (int i = 0; i < text.length(); i++){
        CharWeight[text[i]]++;
    }
    std::vector<std::pair<char, unsigned int>> symbols;
    for(int i = 0; i < 256; i++){
        if(CharWeight[i]) symbols.push_back({i, CharWeight[i]});
    }
    Symbol_comp comp;
    std::sort(symbols.begin(), symbols.end(), comp);
    std::map<char, Shannon_Fano> table;
    Shannon_Fano_Table_r(symbols, table, 0, symbols.size());
    return table;
}

void Shannon_Fano_Table_r(std::vector<std::pair<char, unsigned int>>& symbols, std::map<char, Shannon_Fano>& table, int l, int r){
    if(l >= r-1) return;
    int mindiff = INT_MAX;
    int minm = l;
    int sym1 = symbols[0].second;
    int sym2 = 0;
    
    for(int i = l+1; i < r; i++){
        sym2 += symbols[i].second;
    }

    mindiff = abs(sym2 - sym1);
    for(int i = l+1; i < r; i++){
        sym1 += symbols[i].second;
        sym2 -= symbols[i].second;
        if(abs(sym2 - sym1) < mindiff){
            mindiff = abs(sym2 - sym1);
            minm = i;
        }
    }

    for(int i = l; i <= minm; i++){
        table[symbols[i].first].length++;
        table[symbols[i].first].data <<= 1;
    }

    for(int i = minm+1; i < r; i++){
        table[symbols[i].first].length++;
        table[symbols[i].first].data <<= 1;
        table[symbols[i].first].data |= 1;
    }

    std::cout << "Таблица кодов Шеннона-Фано: \n";
    for(auto i = table.begin(); i != table.end(); i++){
        std::cout << i->first << " | " << i->second << "\n";
    }
    std::cout << std::endl;

    Shannon_Fano_Table_r(symbols, table, l, minm+1);
    Shannon_Fano_Table_r(symbols, table, minm+1, r);
}

void Shannon_Fano_encode(std::ifstream &file_in,std::ofstream &file_out){
    file_in.seekg(0,std::ios::end);//изменение текущего указателя на чтение-запись файла
    size_t file_size = file_in.tellg();
    file_out.write((char*)&file_size, sizeof(file_size));
    std::string buff(file_size,'\0');//Узнаем размер файла
    file_in.seekg(0);//Переходим в конец
    file_in.read(&buff[0],file_size);//Считываем весь файл в буффер
    std::map<char,Shannon_Fano> Table = Shannon_Fano_Table(buff);
    size_t Table_size = Table.size();
    file_out.write((char*)&Table_size, sizeof(size_t));
    for(auto i = Table.begin(); i != Table.end(); i++){//Записываем таблицу кодов в файл
        file_out.write((char*)&i->first, sizeof(i->first));
        file_out.write((char*)&i->second.data, sizeof(i->second.data));
        file_out.write((char*)&i->second.length, sizeof(i->second.length));
    }
    unsigned char byte = 0;//Некоторый буффер, при заполнении которого записываем значение в файл
    size_t bit = 0;//
    for (size_t i = 0; i < buff.length(); i++){
        Shannon_Fano c = Table[buff[i]];
        for (size_t j = 0; j < c.length; j++){
            if(c.data & (1 << (c.length - 1 - j))){
                byte |= 1 << (7 - bit);
            }
            if(++bit == 8){
                file_out.write((char*)&byte,sizeof(byte));
                byte = 0;
                bit = 0;
            }
        }
    }
    file_out.write((char*)&byte,sizeof(byte));
}

void Shannon_Fano_decode(std::ifstream &file_in,std::ofstream &file_out){
    size_t file_size;
    file_in.read((char*)&file_size, sizeof(file_size));
    std::map<char,Shannon_Fano> Table;
    size_t Table_size;
    file_in.read((char*)&Table_size,sizeof(Table_size));
    for (size_t i = 0; i < Table_size; i++){
        std::pair<char,Shannon_Fano> p;
        file_in.read((char*)&p.first,sizeof(p.first));
        file_in.read((char*)&p.second.data,sizeof(p.second.data));
        file_in.read((char*)&p.second.length,sizeof(p.second.length));
        Table[p.first] = p.second;
        
    }

    unsigned char byte = 0;
    int bit = 0;
    int ch;
    while((ch = file_in.get()) != std::char_traits<char>::eof()){
        char c = ch;
        for(size_t bit_c = 0; bit_c < 8; bit_c++){
            if(c & (1 << (7 - bit_c))){
                byte |= 1 << (7 - bit);
            }
            Shannon_Fano code;
            code.data = byte >> (7 - bit);
            code.length = bit + 1;
            for (auto i = Table.begin(); i != Table.end(); i++){
                if(i->second == code){
                    file_out << i->first;
                    bit = -1;
                    byte = 0;
                    if(--file_size == 0){
                        return;
                    }
                    break;
                }
            }
            bit++;
        }
    }
}

int main(){
    std::ifstream file_in("Code"); 
    std::ofstream file_out("Encode");
    Shannon_Fano_encode(file_in,file_out);
    file_in.close();
    file_out.close();
    std::ifstream file_in2("Encode"); 
    std::ofstream file_out2("Decode");
    Shannon_Fano_decode(file_in2,file_out2);
    file_in2.close();
    file_out2.close();
}