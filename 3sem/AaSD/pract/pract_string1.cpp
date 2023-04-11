#include <iostream>
#include <string>
#include <algorithm>

int main(){
    using namespace std;
    cout << "Введите слово: ";
    string word;
    cin >> word;

    //transform(word.begin(), word.end(), word.begin(), ::tolower);
    string reverse_word = word;
    reverse(reverse_word.begin(), reverse_word.end());

    if(reverse_word == word) cout << "Палиндром";
    else cout << "Не палиндром!";
    cout << "\n";
    return 0;
}