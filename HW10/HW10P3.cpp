#include "../header/MyGraph.h"
#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
    int v, e, from, to;
    cin >> v >> e;
    graph<int> g(v);
    for (int i = 0; i < v; ++i)
    {
        g.add_vertex(i);
    }
    for (int i = 0; i < e; ++i)
    {
        cin >> from >> to;
        g.add_edge(from, to);
        g.add_edge(to, from);
    }
    for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
        {
            cout << setw(4) << g.mat[i*v+j] << ' ';
        }
        cout << endl;
    }
    vector<int> printed;
    //     for (auto& v: g.vertexes)
    // {
    //     v.c = color::white;
    //     v.key = INF;
    //     v.p = nullptr;
    // }
    // for (auto& v: g.vertexes)
    // {
    //     auto itr = find(printed.begin(), printed.end(), &v);
    //     int i = 0;
    //     if (itr == printed.end())
    //     {
    //         cout << '{';
    //         g.DFS_adj_table(v, [&printed, &i](vertex<int>& v) {printed.push_back(&v); ++i;});
    //         for (int j = i; j >= 1; --j)
    //         {
    //             cout << (**(printed.end()-j)).value;
    //             if (j != 1) cout << ' ';
    //         }
    //         cout << '}';
    //     }
    // }
    // cout << endl;
    // printed.clear();
    for (auto& v: g.vertexes)
    {
        auto itr = find(printed.begin(), printed.end(), v.value);
        if (itr == printed.end())
        {
            int i = 0;
            cout << '{';
            g.BFS_adj_mat(v.value, [&printed, &i](int v) {printed.push_back(v); ++i;});
            for (int j = i; j >= 1; --j)
            {
                cout << *(printed.end()-j);
                if (j != 1) cout << ' ';
            }
            cout << '}';
        }
    }
    cout << endl;
}