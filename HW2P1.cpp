#include <iostream>
#include <algorithm>
#include <cstdint>
#include "MyVec.h"
using namespace std;
 
typedef int16_t Int;
int main()
{
    size_t n, i, j;
    Int temp, x, y;
    cin >> n;
    alan::vector<Int> data;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> temp;
        cout << temp << " ";
        data.push_back(temp);
    }
    cout << endl;
    cin >> i >> x >> j >> y;
    if (i > data.size() || i < 1)
    {
        cout << -1 << endl;
    }
    else
    {
        data.insert(data.begin() + i -1, x);
        for (auto v: data) cout << v << " ";
        cout << endl;
    }
    if (j > data.size() || j < 1)
    {
        cout << -1 << endl;
    }
    else
    {
        data.erase(data.begin() + j - 1);
        for (auto v: data) cout << v << " ";
        cout << endl;
    }
    auto pos = find(data.begin(), data.end(), y);
    if (pos == data.end())
    {
        cout << -1 << endl;
    }
    else
    {
        cout << pos - data.begin() + 1 << endl;
    }
}