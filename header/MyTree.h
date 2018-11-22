#ifndef TREE_BASE_H
#define TREE_BASE_H
#include "MyStack.h"
#include "MyQueue.h"
#include <iostream>
namespace alan
{
	template <class T>
	struct node
	{
		T value;
		int weight;
		node<T>* left;
		node<T>* right;
	};

	template <class T>
	class tree_base {
	public:
		tree_base(): tree(nullptr) {}
		tree_base(const tree_base& x): tree(copy(x.tree)) {}
		tree_base(tree_base&& x): tree(x.tree) {x.tree = nullptr;}
		tree_base& operator=(tree_base x) {auto temp = tree; tree = x.tree, x.tree = temp; return *this;}
		virtual ~tree_base() { clear(); }
		node<T>* push_left(const T& x, node<T> *pos);
		node<T>* push_right(const T& x, node<T> *pos);
		node<T>* insert_left(tree_base& t, node<T> *pos);
		node<T>* insert_right(tree_base& t, node<T> *pos);
		template <class Oper> void preorder_traverse(Oper op);
		template <class Oper> void inorder_traverse(Oper op);
		template <class Oper> void postorder_traverse(Oper op);
		template <class Oper> void level_traverse(Oper op);
        size_t leaf_count();
        size_t node_count();
        size_t depth();
        void reverse();
		node<T>* root() {return tree;}
		void clear(); 
	private:
		node<T>* copy(node<T>* from);
        void reverse(node<T>* t);
        size_t leaf_count(node<T>* t);
        size_t node_count(node<T>* t);
        size_t depth(node<T>* t);
		template <class Oper> void preorder_traverse(Oper op, node<T>* t);
		template <class Oper> void inorder_traverse(Oper op, node<T>* t);
		template <class Oper> void postorder_traverse(Oper op, node<T>* t);
		void clear(node<T>* t);
		node<T> *tree;
	};

	template <class T>
	node<T>* tree_base<T>::insert_left(tree_base<T> &t, node<T> *pos)
	{
		if (pos)
		{
			pos->left = t.root();
			t.tree = nullptr;
			return pos->left;
		}
		else
		{
			tree = t.tree;
			t.tree = nullptr;
			return tree;
		}
	}

	template <class T>
	node<T>* tree_base<T>::insert_right(tree_base<T> &t, node<T> *pos)
	{
		if (pos)
		{
			pos->right = t.root();
			t.tree = nullptr;
			return pos->right;
		}
		else
		{
			tree = t.tree;
			t.tree = nullptr;
			return tree;
		}
	}

    template <class T>
    void tree_base<T>::reverse()
    {
        reverse(tree);
    }

    template <class T>
    void tree_base<T>::reverse(node<T>* t)
    {
        if (t)
        {
            auto temp = t->left;
            t->left = t->right;
            t->right = temp;
            reverse(t->left);
            reverse(t->right);
        }
    }

    template <class T>
    size_t tree_base<T>::depth()
    {
        return depth(tree);
    }

    template <class T>
    size_t tree_base<T>::depth(node<T>* t)
    {
        if (t)
        {
            auto left = depth(t->left);
            auto right = depth(t->right);
            return left > right ? left + 1 : right + 1;
        }
        else return 0;
    }

    template <class T>
    size_t tree_base<T>::node_count()
    {
        return node_count(tree);
    }

    template <class T>
    size_t tree_base<T>::node_count(node<T>* t)
    {
        if (t) return node_count(t->left) + node_count(t->right) + 1;
        else return 0;
    }

    template <class T>
    size_t tree_base<T>::leaf_count()
    {
        return leaf_count(tree);
    }

    template <class T>
    size_t tree_base<T>::leaf_count(node<T>* t)
    {
        if (t)
        {
            if (!t->left && !t->right) return 1;
            else return leaf_count(t->left) + leaf_count(t->right);
        }
        else return 0;
    }

	template <class T>
	node<T>* tree_base<T>::copy(node<T>* from)
	{
		if (from)
		{
			node<T>* to;
			to = new node<T>{from->value, copy(from->left), copy(from->right)};
			return to;
		}
		else return nullptr;
	}

	template <class T>
	node<T>* tree_base<T>::push_left(const T& x, node<T> *pos)
	{
		if (pos)
		{
			pos->left = new node<T>{x, pos->left, nullptr};
			return pos->left;
		}
		else
		{
			tree = new node<T>{x, nullptr, nullptr};
			return tree;
		}
	}

	template <class T>
	node<T>* tree_base<T>::push_right(const T& x, node<T> *pos)
	{
		if (pos) 
		{
			pos->right = new node<T>{x, nullptr, pos->right};
			return pos->right;
		}
		else
		{
			tree = new node<T>{x, nullptr, nullptr};
			return tree;
		}
	}

    template <class T>
    template <class Oper> void tree_base<T>::level_traverse(Oper op)
    {
        if (tree)
        {
            auto q = deque<node<T>*>(512);
            q.push(tree);
            while (!q.empty())
            {
                auto temp = q.pop();
                op(temp->value);
                if (temp->left) q.push(temp->left);
                if (temp->right) q.push(temp->right);
            }
        }
    }

	template <class T>
	template <class Oper> void tree_base<T>::postorder_traverse(Oper op)
	{
		postorder_traverse(op, tree);
	}

	template <class T>
	template <class Oper> void tree_base<T>::postorder_traverse(Oper op, node<T>* t)
	{
		if (t)
		{
			postorder_traverse(op, t->left);
			postorder_traverse(op, t->right);
			op(t->value);
		}
	}

	template <class T>
	template <class Oper> void tree_base<T>::inorder_traverse(Oper op)
	{
		inorder_traverse(op, tree);
	}

	template <class T>
	template <class Oper> void tree_base<T>::inorder_traverse(Oper op, node<T>* t)
	{
		if (t)
		{
			inorder_traverse(op, t->left);
			op(t->value);
			inorder_traverse(op, t->right);
		}
	}

	template <class T>
	template <class Oper> void tree_base<T>::preorder_traverse(Oper op)
	{
		preorder_traverse(op, tree);
	}

	template <class T>
	template <class Oper> void tree_base<T>::preorder_traverse(Oper op, node<T>* t)
	{
		if (t)
		{
			op(t->value);
			preorder_traverse(op, t->left);
			preorder_traverse(op, t->right);
		}
	}

	template <class T>
	void tree_base<T>::clear()
	{
		clear(tree);
		tree = nullptr;
	}

	template <class T>
	void tree_base<T>::clear(node<T>* t)
	{
		if (t)
		{
			clear(t->left);
			clear(t->right);
			delete t;
		}
	}

	template <class T, class Itr, class Pred>
	tree_base<T> preoder_initial_tree(Itr first, Itr last, Pred p)
	{
		auto s = stack<node<T>*>(512);
		auto tree = tree_base<T>();
		auto node = tree.root();
		auto flag = true;
		for (; first != last; ++first)
		{
			if (flag)
			{
				if (p(*first))
				{
					node = tree.push_left(*first, node);
					s.push(node);
				}
				else flag = false;
			}
			else
			{
				if (p(*first))
				{
					node = tree.push_right(*first, s.pop());
					s.push(node);
					flag = true;
				}
				else s.pop();
			}
		}
		return tree;
	}
}

#endif