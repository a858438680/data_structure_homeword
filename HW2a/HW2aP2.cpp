#include <queue>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "../header/MyTree.h"
using namespace std;
void Huffman(alan::node<int>* n, std::string code, vector<pair<int, string>>& result)
{
	stringstream ss;
	if ((!(n->left)) && (!(n->right))) {
		ss << n->value << " " << code << endl;
		result.push_back(make_pair(n->value, ss.str()));
	}
	else {
		Huffman(n->left, code + "0", result);
		Huffman(n->right, code + "1", result);
	}
}

int main()
{
	int n, temp;
	bool right;
	using item = pair<int, pair<int, bool>>;
	auto cmp = [](const item& lhs, const item& rhs) { return lhs.first < rhs.first; };
	priority_queue<item, std::vector<item>, decltype(cmp)> data(cmp);
	vector<alan::node<int>*> nodes;
	cin >> n;
	for (int i = 0; i < 2 * n - 1; ++i)
	{
		cin >> temp;
		cin >> temp;
		cin >> right;
		temp = !temp ? 2 * n : temp;
		data.push(make_pair(temp, make_pair(i + 1, right)));
	}
	alan::tree_base<int> tree;
	tree.push_left(data.top().second.first, tree.root());
	data.pop();
	nodes.push_back(tree.root());
	while (!data.empty())
	{
		auto next = data.top();
		data.pop();
		auto father_itr = find_if(nodes.begin(), nodes.end(), [&next](alan::node<int>* p) {
			return p->value == next.first;
		});
		auto father = *father_itr;
		alan::node<int>* next_node;
		if (next.second.second) next_node = tree.push_right(next.second.first, father);
		else next_node = tree.push_left(next.second.first, father);
		nodes.push_back(next_node);
	}
	vector<pair<int, string>> result;
	Huffman(tree.root(), "", result);
	sort(result.begin(), result.end(), [](const pair<int, string>& lhs, const pair<int, string>& rhs) {
		return lhs.first < rhs.first;
	});
	for (auto& v : result)
	{
		cout << v.second;
	}
}