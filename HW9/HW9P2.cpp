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

template <class Oper>
void inorder_threaded_traverse(node* t, Oper op, char c)
{
    std::string prev;
    std::string succ;
    auto last = static_cast<node*>(nullptr);
    auto found = false;
    auto end = false;
    while (t && !(t->lflag)) t = t->left;
    while (t)
    {
        if (found && !end)
        {
            succ = "succ is ";
            succ.push_back(t->value);
            succ.push_back(t->rflag?'1':'0');
            succ.push_back('\n');
            end = true;
        }
        if (!found && t->value == c)
        {
            found = true;
            if (last)
            {
                prev = "prev is ";
                prev.push_back(last->value);
                prev.push_back(last->lflag?'1':'0');
                prev.push_back('\n');
            }
            else prev = "prev is NULL\n";
        }
        last = t;
        op(t);
        while (t && t->rflag)
        {
            t = t->right;
            if (t)
            {
                if (found && !end)
                {
                    succ = "succ is ";
                    succ.push_back(t->value);
                    succ.push_back(t->rflag?'1':'0');
                    succ.push_back('\n');
                    end = true;
                }
                if (!found && t->value == c)
                {
                    found = true;
                    if (last)
                    {
                        prev = "prev is ";
                        prev.push_back(last->value);
                        prev.push_back(last->lflag?'1':'0');
                        prev.push_back('\n');
                    }
                    else prev = "prev is NULL\n";
                }
                last = t;
                op(t);
            }
        }
        if (t)
        {
            t = t->right;
            while (!(t->lflag)) t = t->left;
        }
    }
    if (!found) cout << "\nNot found\n";
    else if (!end) cout << "\nsucc is NULL\n" << prev;
    else cout << '\n' << succ << prev;
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
    char c;
    auto tree_str = string();
    cin >> tree_str;
    cin >> c;
    auto tree = preorder_initial_tree(tree_str.begin(), tree_str.end(), [](char c){ return c != '#';});
    auto last_node = new node*(nullptr);
    inorder_thread(tree, last_node);
    inorder_threaded_traverse(tree, [](node *n){cout << n->value;}, c);
}