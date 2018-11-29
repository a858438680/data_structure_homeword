#include <iostream>
#include <queue>
using namespace std;

int main()
{
    using node = pair<int, int>;
    auto cmp = [](const node& lhs, const node& rhs){ return lhs.first > rhs.first; };
    priority_queue<node, std::vector<node>, decltype(cmp)> data(cmp);
    int n, temp;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> temp;
        data.push(make_pair(temp, 0));
    }
    while(data.size() > 1)
    {
        auto first = data.top();
        data.pop();
        auto second = data.top();
        data.pop();
        data.push(make_pair(first.first + second.first, first.first+first.second+second.first+second.second));
    }
    std::cout << data.top().second << std::endl;
}
