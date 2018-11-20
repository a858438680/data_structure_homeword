#include "../header/MyTree.h"
#include <iostream>
#include <string>

using namespace std;
void show_rotate_90(alan::node<char>* t, size_t depth)
{
    if (t)
    {
        show_rotate_90(t->right, depth+1);
        cout << string(5*depth, ' ') << t->value << endl;
        show_rotate_90(t->left, depth+1);
    }
}

int main()
{
    auto tree_str = string();
    cin >> tree_str;
    auto tree = alan::preoder_initial_tree<char>(tree_str.begin(), tree_str.end(), [](char c){ return c != '#';});
    tree.preorder_traverse([](char c){ cout << c; });
    cout << endl;
    tree.inorder_traverse([](char c){ cout << c; });
    cout << endl;
    tree.postorder_traverse([](char c){ cout << c; });
    cout << endl;
    tree.level_traverse([](char c){ cout << c; });
    cout << endl;
    show_rotate_90(tree.root(), 0);
}