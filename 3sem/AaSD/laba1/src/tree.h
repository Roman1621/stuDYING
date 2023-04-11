#ifndef TREE_H
#define TREE_H

#include <vector>
using namespace std;

class tree_node{
    public:
        vector <tree_node*> children;
        void add_child(tree_node* node);
};

class tree{
    private:
        tree_node* root;

        unsigned int private_get_height(tree_node* top);
        void destroyer(tree_node* top);
    
    public:
        tree(vector <int>& parent_index);
        ~tree();
        unsigned int get_height();
};

#endif
