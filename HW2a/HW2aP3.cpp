#include <iostream>
#include <string>
#include "../header/MyTree.h"
using namespace std;
int main()
{
	int n;
	cin >> n;
	alan::tree_base<char> huffman_tree;
	huffman_tree.push_left('\0', huffman_tree.root());
	for (int i = 0; i < n; ++i)
	{
		int value;
		char c;
		string code;
		cin >> value >> code;
		c = static_cast<char>(value);
		auto node = huffman_tree.root();
		for (auto v : code)
		{
			if (v == '1')
				if (node->right) node = node->right;
				else node = huffman_tree.push_right(c, node);
			if (v == '0')
				if (node->left) node = node->left;
				else node = huffman_tree.push_left(c, node);
		}
	}
	string code;
	cin >> code;
	auto node = huffman_tree.root();
	for (auto v : code)
	{
		if ((!(node->left)) && (!(node->right)))
		{
			cout << node->value;
			node = huffman_tree.root();
		}
		node = (v == '1' ? node->right : node->left);
	}
	if ((!(node->left)) && (!(node->right)))
	{
		cout << node->value;
	}
	cout << endl;
}