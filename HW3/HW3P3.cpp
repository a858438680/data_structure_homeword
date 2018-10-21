#include <iostream>
#include "MyList.h"
 
template<class InputIt, class T>
InputIt find(InputIt first, InputIt last, const T& value)
{
    for (; first != last; ++first) {
        if (*first == value) {
            return first;
        }
    }
    return last;
}
 
using namespace std;
int main()
{
    size_t n;
    int temp;
    alan::forward_list<int> data;
    alan::forward_list<int> existed;
    cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        if (cin >> temp) data.push_front(temp);
    }
    data.reverse();
    for (auto itr = data.begin(); itr != data.end(); ++itr)
    {
        auto first = find(existed.begin(), existed.end(), *itr);
        if (first == existed.end()) existed.push_front(*itr);
    }
    existed.reverse();
    for (auto v: existed) cout << v << " ";
    cout << endl;
}