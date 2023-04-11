#include "tree.h"

void tree_node::add_child(tree_node* node){
    children.push_back(node);
}

tree::tree(vector <int>& parent_index){
    root = nullptr;
    vector <tree_node*> nodes(parent_index.size());
    for(int i = 0; i < parent_index.size(); i++)
        nodes[i] = new tree_node();
    for(int i = 0; i < parent_index.size(); i++){
        int element = parent_index[i];
        if(element == -1)
            root = nodes[i];
        else
            nodes[element]->add_child(nodes[i]);
    }
}

tree::~tree(){
    if(root){
        destroyer(root);
    }
}

void tree::destroyer(tree_node* top){
    if(!top) return;
    
    size_t n = top->children.size();
    for(size_t i = 0; i < n; i++){
        destroyer(top->children[i]);
    }
    
    delete top;
}

unsigned int tree::get_height(){
    return private_get_height(root);
}

unsigned int tree::private_get_height(tree_node* top){
    if(!top) return 0;
    unsigned int top_max = 0;
    for(size_t i = 0; i < top->children.size(); i++){
        unsigned int height = private_get_height(top->children[i]);
        if(height > top_max) top_max = height;
    }
    return top_max + 1;
}
