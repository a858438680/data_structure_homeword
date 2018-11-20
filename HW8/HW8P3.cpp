#include "../header/MyTree.h"
#include <iostream>
#include <string>

using namespace std;
int main()
{
    auto tree_str = string();
    cin >> tree_str;
    auto tree = alan::preoder_initial_tree<char>(tree_str.begin(), tree_str.end(), [](char c){ return c != '#';});
    auto s = alan::stack<alan::node<char>*>(512);
    auto t = tree.root();
    if (t)
    {
        while (t || !s.empty())
        {
            if (t)
            {
                s.push(t);
                cout << "push " << t->value << endl;
                t = t->left;
            }
            else
            {
                t = s.pop();
                cout << "pop" << endl;
                cout << t->value << endl;
                t = t->right;
            }
        }
    }
}