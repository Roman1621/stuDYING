#include <iostream>
#include <string>
#include <algorithm>

int get_vowels_quant(std::string& sentence, char fchar){
    int quant = 0;
    auto is_vowel = sentence.find(fchar);
    while(is_vowel != std::string::npos){
        ++quant;
        is_vowel = sentence.find(fchar, is_vowel+1);
    }
    return quant;
}

int main(){
    using namespace std;

    cout << "Введите предложение: " << endl;
    string sentence;
    getline(cin, sentence);

    int sentence_number = get_vowels_quant(sentence, 'a');
    sentence_number += get_vowels_quant(sentence, 'A');
    sentence_number += get_vowels_quant(sentence, 'e');
    sentence_number += get_vowels_quant(sentence, 'E');
    sentence_number += get_vowels_quant(sentence, 'y');
    sentence_number += get_vowels_quant(sentence, 'Y');
    sentence_number += get_vowels_quant(sentence, 'u');
    sentence_number += get_vowels_quant(sentence, 'U');
    sentence_number += get_vowels_quant(sentence, 'i');
    sentence_number += get_vowels_quant(sentence, 'I');
    sentence_number += get_vowels_quant(sentence, 'o');
    sentence_number += get_vowels_quant(sentence, 'O');

    cout << "Количество гласных в предложении: " << sentence_number << endl;
    return 0;
}