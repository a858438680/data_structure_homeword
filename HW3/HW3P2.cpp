#include <iostream>
#include <algorithm>
#include "MyList.h"
 
using namespace std;
int main()
{
    size_t n;
    int temp;
    alan::forward_list<int> data;
    cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        if(cin >> temp) data.push_front(std::move(temp));
    }
    for (auto v: data) cout << v << " ";
    cout << endl;
    data.reverse();
    data.remove_if([](int x) {return x%3 != 0;});
    for (auto v: data) cout << v << " ";
    cout << endl;
}