#include "../header/MyStack.h"
#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct node {
    char value;
    bool lflag;
    bool rflag;
    node* left;
    node* right;
    node(char c): value(c), lflag(false), rflag(false), left(nullptr), right(nullptr) {}
    node(char c, node* l, node *r): value(c), lflag(false), rflag(false), left(l), right(r) {}
};

void preorder_thread(node* t, node** last_node)
{
    if (t)
    {
        if (*last_node && (*last_node)->rflag) (*last_node)->right = t;
        if (t->left) t->lflag = false;
        else
        {
            t->lflag = true;
            t->left = *last_node;
        }
        if (t->right) t->rflag = false;
        else t->rflag = true;
        *last_node = t;
        if (!(t->lflag)) preorder_thread(t->left, last_node);
        if (!(t->rflag)) preorder_thread(t->right, last_node);
    }
}

void inorder_thread(node* t, node** last_node)
{
    if (t)
    {
        if (!(t->lflag)) inorder_thread(t->left, last_node);
        if (*last_node && (*last_node)->rflag) (*last_node)->right = t;
        if (t->left) t->lflag = false;
        else
        {
            t->lflag = true;
            t->left = *last_node;
        }
        if (t->right) t->rflag = false;
        else t->rflag = true;
        *last_node = t;
        if (!(t->rflag)) inorder_thread(t->right, last_node);
    }
}

template <class Oper>
void preorder_threaded_traverse(node* t, Oper op)
{
    while(t)
    {
        op(t);
        if (!(t->lflag)) t = t->left;
        else t = t->right;
    }
}

void show_rotate_90(node* t, size_t depth)
{
    if (t)
    {
        if (!(t->rflag)) show_rotate_90(t->right, depth+1);
        cout << string(5*depth, ' ') << t->value << t->lflag << t->rflag << endl;
        if (!(t->lflag)) show_rotate_90(t->left, depth+1);
    }
}

node* push_left(node* &tree, char x, node *pos)
{
    if (pos)
    {
        pos->left = new node(x, pos->left, nullptr);
        return pos->left;
    }
    else
    {
        tree = new node(x, nullptr, nullptr);
        return tree;
    }
}

node* push_right(node* &tree, char x, node *pos)
{
    if (pos)
    {
        pos->right = new node(x, nullptr, pos->right);
        return pos->right;
    }
    else
    {
        tree = new node(x, nullptr, nullptr);
        return tree;
    }
}

template <class Itr, class Pred>
node* preorder_initial_tree(Itr first, Itr last, Pred p)
{
    auto s = alan::stack<node*>(512);
    auto t = static_cast<node*>(nullptr);
    auto node = t;
    auto flag = true;
    for (; first != last; ++first)
    {
        if (flag)
        {
            if (p(*first))
            {
                node = push_left(t, *first, node);
                s.push(node);
            }
            else flag = false;
        }
        else
        {
            if (p(*first))
            {
                node = push_right(t, *first, s.pop());
                s.push(node);
                flag = true;
            }
            else s.pop();
        }
    }
    return t;
}

int main()
{
    auto tree_str = string();
    cin >> tree_str;
    auto tree = preorder_initial_tree(tree_str.begin(), tree_str.end(), [](char c){ return c != '#';});
    auto last_node = new node*(nullptr);
    preorder_thread(tree, last_node);
    show_rotate_90(tree, 0);
    preorder_threaded_traverse(tree, [](node *n){cout << n->value;});
    cout << endl;
}