#include <iostream>
#include <algorithm>
#include "MyVec.h"
using namespace std;
 
int main()
{
    alan::vector<uint16_t> data;
    size_t n;
    uint16_t x, temp;
    cin >> n;
    data.reserve(n);
    for (size_t i = 0; i < n; ++i)
        if (cin >> temp)
            data.push_back(temp);
    cin >> x;
    auto pos = find(data.begin(), data.end(), x);
    if (pos == data.end()) cout << -1 << endl;
    else {
        alan::vector<uint16_t> new_data;
        for_each(data.begin(), data.end(), [&new_data, x](uint16_t v) {if (v != x) new_data.push_back(v); });
        for (auto v : new_data) { cout << v << ' '; }
    }
}