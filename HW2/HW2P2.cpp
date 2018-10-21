#include <iostream>
#include <algorithm>
#include "MyVec.h"
using namespace std;
 
int main()
{
    alan::vector<uint16_t> data;
    uint16_t n, i_num, d_num;
    while (cin >> n && n != 0)
        data.push_back(n);
    sort(data.begin(), data.end());
    cin >> i_num >> d_num;
    auto pos = find_if(data.begin(), data.end(), [i_num](uint16_t x) {return x >= i_num; });
    cout << pos - data.begin() + 1 << endl;
    data.insert(pos, i_num);
    pos = find(data.begin(), data.end(), d_num);
    if (pos == data.end())
        cout << -1 << endl;
    else
    {
        cout << pos - data.begin() + 1 << endl;
        data.erase(pos);
    }
    for_each(data.begin(), data.end(), [](uint16_t x) {cout << x << ' '; });
}