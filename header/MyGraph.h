#ifndef MY_GRAPH_H
#define MY_GRAPH_H
#include <map>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <deque>
#define INF 0x7fffffff

enum class color {
    white,
    gray,
    black
};

template <class T>
struct vertex {
    T value;
    vertex<T> *p;
    color c;
    int key;
    vertex(T x): value(x), p(nullptr), c(color::white), key(0){}
    bool operator==(const T& x) { return value == x; }
};

template <class T>
struct edge {
    vertex<T> *u;
    vertex<T> *v;
    int weight;
};

template <class T>
struct graph {
    graph(int n): mat(new int[n*n]), n(n) {}
    std::vector<vertex<T>> vertexes;
    std::vector<edge<T>> edges;
    std::map<T, std::list<std::pair<vertex<T>*, int>>> adj;
    int *mat;
    int n;
    void add_vertex(T x)
    {
        vertexes.emplace_back(x);
        adj[x] = std::list<std::pair<vertex<T>*, int>>();
    }

    void add_edge(T u, T v)
    {
        auto first = std::find_if(vertexes.begin(), vertexes.end(), [u](vertex<T> p){return p == u;});
        auto second = std::find_if(vertexes.begin(), vertexes.end(), [v](vertex<T> p){return p == v;});
        edges.push_back(edge<T>{&(*first), &(*second), 1});
        adj[(*first).value].push_front(std::make_pair(&(*second), 1));
        mat[(first-vertexes.begin())*n+(second-vertexes.begin())] = 1;
    }
    
    void add_edge(T u, T v, int w)
    {
        auto first = std::find_if(vertexes.begin(), vertexes.end(), [u](vertex<T> p){return p == u;});
        auto second = std::find_if(vertexes.begin(), vertexes.end(), [v](vertex<T> p){return p == v;});
        edges.push_back(edge<T>{&(*first), &(*second), w});
        adj[(*first).value].push_front(std::make_pair(&(*second), w));
        mat[(first-vertexes.begin())*n+(second-vertexes.begin())] = w;
    }

    template <class Oper>
    void BFS_adj_table(vertex<T> &s, Oper op)
    {
        for (auto& v: vertexes)
        {
            v.c = color::white;
            v.key = INF;
            v.p = nullptr;
        }
        s.c = color::gray;
        s.key = 0;
        s.p = nullptr;
        std::deque<vertex<T>*> Q;
        Q.push_back(&s);
        while (!Q.empty())
        {
            auto& u = *(Q.front());
            Q.pop_front();
            for (auto pv: adj[u.value])
            {
                auto& v = *(pv.first);
                if (v.c == color::white)
                {
                    v.c = color::gray;
                    v.key = u.key + 1;
                    v.p = &u;
                    Q.push_back(&v);
                }
            }
            u.c = color::black;
            op(u);
        }
    }

    template <class Oper>
    void DFS_adj_table(vertex<T> &u, Oper op)
    {
        u.c = color::gray;
        op(u);
        for (auto& pv: adj[u.value])
        {
            auto& v = *(pv.first);
            if (v.c == color::white)
            {
                v.p = &u;
                DFS_adj_table(v, op);
            }
        }
        u.c = color::black;
    }

    template <class Oper>
    void BFS_adj_mat(int i, Oper op)
    {
        for (auto& v: vertexes)
        {
            v.c = color::white;
        }
        std::deque<int> Q;
        Q.push_back(i);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop_front();
            vertexes[u].c = color::gray;
            for (int j = i*n; j < i*n+n; ++j)
            {
                if (mat[j] != 0 && vertexes[j-i*n].c == color::white)
                {
                    vertexes[j-i*n].c = color::gray;
                    Q.push_back(j-i*n);
                }
            }
            op(u);
            vertexes[u].c = color::black;
        }
    }
};
#endif