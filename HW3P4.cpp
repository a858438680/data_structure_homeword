#include <iostream>
#include "MyList.h"
using namespace std;

int main()
{
    int temp;
    alan::forward_list<int> data1, data2;
    while (cin >> temp, temp != 0)
    {
        data1.push_front(temp);
    }
    while (cin >> temp, temp != 0)
    {
        data2.push_front(temp);
    }
    data1.sort();
    data2.sort();
    data1.merge(data2);
    for (auto v: data1) cout << v << " ";
    cout << endl;
}