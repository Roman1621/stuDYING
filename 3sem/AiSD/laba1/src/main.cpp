#include <iostream>
#include "tree.h"
#include <vector>

int main(){
    int n = 0;
    cin >> n;
    vector <int> parent_index(n);
    for(int i = 0; i < n; i++){
        cin >> parent_index[i];
    }

    tree w_tree(parent_index);
    cout << w_tree.get_height() << endl;
    return 0;
}
