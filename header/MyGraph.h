#ifndef MY_GRAPH_H
#define MY_GRAPH_H
#include <map>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

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
};
#endif