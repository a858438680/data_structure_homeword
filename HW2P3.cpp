#include <iostream>
#include <algorithm>
#include <cstdint>
#include "MyVec.h"
using namespace std;
 
typedef int16_t Int;
int main()
{
    alan::vector<Int> data1;
    alan::vector<Int> data2;
    alan::vector<Int> data;
    Int temp;
    while (cin >> temp, temp != 0)
    {
        data1.push_back(temp);
    }
    while (cin >> temp, temp != 0)
    {
        data2.push_back(temp);
    }
    sort(data1.begin(), data1.end());
    sort(data2.begin(), data2.end());
    auto itr1 = data1.begin();
    auto itr2 = data2.begin();
    while(itr1 != data1.end() || itr2 != data2.end())
    {
        if (itr1 == data1.end())
        {
            data.push_back(*itr2);
            ++itr2;
        }
        else if (itr2 ==data2.end())
        {
            data.push_back(*itr1);
            ++itr1;
        }
        else if (*itr1 < *itr2)
        {
            data.push_back(*itr1);
            ++itr1;
        }
        else
        {
            data.push_back(*itr2);
            ++itr2;
        }
    }
    for (auto v: data) cout << v << " ";
    cout << endl;
}