#include <iostream>
#include <algorithm>
#include "MyList.h"
 
using namespace std;
int main()
{
    size_t n, i, j;
    int temp, x, y;
    alan::forward_list<int> data;
    cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        if(cin >> temp) data.push_front(std::move(temp));
    }
    cin >> i >> x >> j >> y;
    for (auto v: data) cout << v << " ";
    cout << endl;
    auto pos = data.before_begin();
    for (size_t j = 0; pos != data.end() && j < i - 1;)
    {
        ++j;
        ++pos;
    }
    if (pos == data.end()) cout << -1 << endl;
    else {
        data.insert_after(pos, x);
        for (auto v: data) cout << v << " ";
        cout << endl;
    }
    pos = data.before_begin();
    auto last = data.begin();
    auto rem = data.begin();
    while (rem = last++, last != data.end());
    last = rem;
    for (size_t i = 0; pos != last && i < j - 1;)
    {
        ++i;
        ++pos;
    }
    if (pos == last) cout << -1 << endl;
    else {
        data.erase_after(pos);
        for (auto v: data) cout << v << " ";
        cout << endl;
    }
    size_t ele = 1;
    for (pos = data.begin(); pos != data.end() && *pos != y; ++pos, ++ele);
    if (pos == data.end()) cout << -1 << endl;
    else {
        cout << ele << endl;
    }
    ele = 0;
    for (pos = data.begin(); pos != data.end(); ++pos, ++ele);
    cout << ele << endl;
}