#include <iostream>
#include <map>

struct Node{
    Node *right, *left;
    long long int k;
};

class Tree{
    Node* root;

    bool check_root(Node* node){
        if(node->left && node->left->k > node->k) return false;
        if(node->right && node->right->k < node->k) return false;
        
        if(node->left && !check_root(node->left)) return false;
        if(node->right && !check_root(node->right)) return false;

        if(node->left && get_max_root(node->left) > node->k) return false;
        if(node->right && get_min_root(node->right) < node->k) return false;

        return true;
    }

    long long int get_max_root(Node* node){
        long long int max = node->k;
        if(node->left && get_max_root(node->left) > max){
            max = get_max_root(node->left);
        }

        if(node->right && get_max_root(node->right) > max){
            max = get_max_root(node->right);
        }
        return max;
    }

    long long int get_min_root(Node* node){
        long long int min = node->k;
        if(node->left && get_min_root(node->left) < min){
            min = get_min_root(node->left);
        }

        if(node->right && get_min_root(node->right) < min){
            min = get_min_root(node->right);
        }
        return min;
    }

    public:
        Tree(){
            int counter = 0;
            std::cin >> counter;

            Node* node = new Node[counter];
            for(int i = 0; i < counter; i++){
                std::cin >> node[i].k;
                int left = 0, right = 0;
                std::cin >> left;
                std::cin >> right;

                if(left == -1) node[i].left = nullptr;
                else node[i].left = &node[left];

                if(right == -1) node[i].right = nullptr;
                else node[i].right = &node[right];
            }
            root = &node[0];
        }

        bool check(){
            return check_root(root);
        }
};

int main(){
    Tree tree;
    if(tree.check()) std::cout << "CORRECT\n";
    else std::cout << "INCORRECT\n";
    return 0;
}