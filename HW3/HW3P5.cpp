#include <iostream>
using namespace std;
 
int* next(int *begin, size_t size, int *pos)
{
    do
    {
        if (pos - begin < size - 1) ++pos;
        else pos = begin;
    } while (!*pos);
    return pos;
}
 
int main()
{
    size_t n, s, m;
    cin >> n >> s >> m;
    --s;
    auto data = new int[n];
    for (size_t i = 0; i < n; ++i)
    {
        data[i] = i + 1;
    }
    auto begin = data + (s + n -1)%n;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            begin = next(data, n, begin);
        }
        cout << *begin << " ";
        *begin = 0;
    }
    cout << endl;
    delete data;
}