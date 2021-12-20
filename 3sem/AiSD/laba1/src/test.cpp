#include<iostream>
#include "tree.h"
#include <cassert>

using namespace std;

void Test0(){
    Tree t_tree({0});
    assert(ttree.count_depth() == 0);
}

void Test1(){
    Tree t_tree1({-1, 0, 4, 0, 3});
    assert(ttree1.count_depth() == 4);
}

void Test2(){
    Tree t_tree2({4, -1, 4, 1, 1});
    assert(ttree2.count_depth() == 3);
}    

void Test3(){
    Tree t_tree3({-1});
    assert(ttree3.count_depth() == 1);    
}

void Test4(){
    Tree t_tree4({-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    assert(ttree4.count_depth() == 6);    
}

int main(){
    Test0();
    Test1();
    Test2();
    Test3();
    Test4(); 
    return 0;
}
