#include <list>
#include <utility>
#include <algorithm>
#include "../header/MyTree.h"
using namespace std;

int main()
{
    int n, temp;
    list<pair<alan::tree_base<int>, int>> forest;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> temp;
        alan::tree_base<int> t;
        t.push_left(temp, t.root());
        forest.push_back(pair<alan::tree_base<int>, int>(t, i));
    }
    if (n < 2);
    else
    {
        auto 
    }
}