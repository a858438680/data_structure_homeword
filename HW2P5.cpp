#include <iostream>
#include <algorithm>
#include <cstdint>
#include "MyVec.h"
using namespace std;
 
typedef int16_t Int;
int main()
{
    size_t n;
    Int temp;
    alan::vector<Int> data;
    cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> temp;
        data.push_back(temp);
    }
    bool exist[10000000];
    for (auto v: data)
    {
        if (!exist[v])
        {
            cout << v << " ";
            exist[v] = true;
        }
    }
    cout << endl;
}