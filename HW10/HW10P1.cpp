#include <iostream>
#include <iomanip>
#include <cctype>
#include "../header/MyGraph.h"

using namespace std;
int main()
{
    int sw, v, e;
    cin >> sw >> v >> e;
    graph<char> g(v);
    char temp, from, to;
    int weight;
    for (int i = 0; i < v; ++i)
    {
        while (cin >> temp, isspace(temp));
        g.add_vertex(temp);
    }
    for (int i = 0; i < e; ++i)
    {
        while (cin >> from, isspace(from));
        while (cin >> to, isspace(to));
        if (sw == 2 || sw == 4) cin >> weight;
        switch (sw) {
            case 1:
                g.add_edge(from, to);
                break;
            case 3:
                g.add_edge(from, to);
                g.add_edge(to, from);
                break;
            case 2:
                g.add_edge(from, to, weight);
                break;
            case 4:
                g.add_edge(from, to, weight);
                g.add_edge(to, from, weight);
        }
    }
    for (auto& v : g.vertexes) cout << v.value << ' ';
    cout << endl;
    for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
        {
            cout << setw(4) << g.mat[i*v+j] << ' ';
        }
        cout << endl;
    }
    for (auto& v : g.vertexes)
    {
        cout << v.value << "-->";
        auto& table = g.adj[v.value];
        for (auto& u : table)
        {
            auto itr = find_if(g.vertexes.begin(), g.vertexes.end(), [u](vertex<char> x){return (u.first)->value == x.value;});
            cout << itr-g.vertexes.begin();
            if (sw == 2 || sw == 4) cout << ',' << u.second;
            cout << ' ';
        }
        cout << endl;
    }
}