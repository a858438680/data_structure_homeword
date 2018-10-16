#include <iostream>
#include "MyList.h"
using namespace std;


int main()
{
    alan::forward_list<int> data;
    data.push_front(1);
    data.push_front(2);
    data.insert_after(data.before_begin(), 3);
    data.reverse();
    for (auto v : data) cout << v << " ";
    cout << endl;
    cout << data.max_size() << endl;
    alan::forward_list<int> new_data;
    cout << new_data.empty() << endl;
    new_data.push_front(4);
    data.merge(new_data);
    for (auto v : data) cout << v << " ";
    cout << endl;
}