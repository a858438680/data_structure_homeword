#ifndef _MY_STATIC_LIST_H_
#define _MY_STATIC_LIST_H_
#include <cstddef>
#include <utility>
namespace alan
{
    template <class T>
    class node;

    template <class T>
    class const_node_iterator;

    template <class T>
    struct node_iterator {
        node_iterator(node<T> *p) : pointer(p) {}
        node_iterator<T>& operator=(const node_iterator<T>& rhs) { pointer = rhs.pointer; return *this;}
        T& operator*() const { return pointer->value; }
        T* operator->() const { return &(pointer->value); }
        node_iterator& operator++() { *this = pointer->next; return *this; }
        node_iterator operator++(int a) {auto ret = *this; this->operator++(); return ret; }
        operator const_node_iterator<T>() { return pointer; }
        operator bool() {return pointer != nullptr; }
        node<T>* pointer;
    };

    template <class T>
    struct const_node_iterator {
        const_node_iterator(const node<T> *p) : pointer(p) {}
        const_node_iterator<T>& operator=(const const_node_iterator<T>& rhs) { pointer = rhs.pointer; }
        const_node_iterator<T>& operator=(const node_iterator<T>& rhs) { pointer = rhs.pointer; }
        const T& operator*() const { return pointer->value; }
        const T* operator->() const { return &(pointer->value); }
        const_node_iterator& operator++() { *this = pointer->next; return *this; }
        const_node_iterator operator++(int a) {auto ret = *this; this->operator++(); return ret; }
        operator bool() {return pointer != nullptr; }
        const node<T>* pointer;
    };

    template <class T>
    struct node {
        node(const T& x) : value(x), next(nullptr) {}
        node(T&& x): value(std::move(x)), next(nullptr) {}
        node(const T& x, node_iterator<T> n) : value(x), next(n) {}
        node(T&& x, node_iterator<T> n) : value(std::move(x)), next(n) {}
        node(node<T>* n) : next(n) {}
        T value;
        node_iterator<T> next;
    };

    template <class T>
    bool operator==(const const_node_iterator<T>& lhs, const const_node_iterator<T>& rhs)
    {
        return lhs.pointer == rhs.pointer;
    }

    template <class T>
    bool operator==(const node_iterator<T>& lhs, const node_iterator<T>& rhs)
    {
        return lhs.pointer == rhs.pointer;
    }

    template <class T>
    bool operator!=(const const_node_iterator<T>& lhs, const const_node_iterator<T>& rhs)
    {
        return lhs.pointer != rhs.pointer;
    }

    template <class T>
    bool operator!=(const node_iterator<T>& lhs, const node_iterator<T>& rhs)
    {
        return lhs.pointer != rhs.pointer;
    }

    template <class T>
    bool operator==(const node_iterator<T>& lhs, const const_node_iterator<T>& rhs)
    {
        return lhs.pointer == rhs.pointer;
    }

    template <class T>
    bool operator==(const const_node_iterator<T>& lhs, const node_iterator<T>& rhs)
    {
        return lhs.pointer == rhs.pointer;
    }

    template <class T>
    bool operator!=(const node_iterator<T>& lhs, const const_node_iterator<T>& rhs)
    {
        return lhs.pointer != rhs.pointer;
    }

    template <class T>
    bool operator!=(const const_node_iterator<T>& lhs, const node_iterator<T>& rhs)
    {
        return lhs.pointer != rhs.pointer;
    }

    template <class T>
    class static_list {
    public:
        // 类型：
        typedef T                                                   value_type;
        typedef value_type&                                         reference;
        typedef const value_type&                                   const_reference;
        typedef node_iterator<T>                                    iterator;
        typedef const_node_iterator<T>                              const_iterator; 
        typedef size_t                                              size_type;
        typedef size_t                                              difference_type;

        static_list(size_t s);
        static_list(const static_list<T>& x);
        static_list(static_list<T>&&);
    
        ~static_list();
        static_list<T>& operator=(static_list<T> x);
    private:
        size_t max_size;
        iterator rest_begin;
        node<T> before_begin_node;
        void swap_after(iterator pos);
        static const iterator the_end_iterator;
    };

    template <class T>
    const node_iterator<T> static_list<T>::the_end_iterator(nullptr);

    template <class T>
    void swap(static_list<T>& lhs, static_list<T>& rhs) noexcept
    {
        using std::swap;
        swap(rhs.before_begin_node, lhs.before_begin_node);
        swap(rhs.rest_begin, lhs.rest_begin);
    }
    
    template <class T>
    void static_list<T>::swap_after(iterator pos)
    {
        auto rem = pos.pointer->next;
        pos.pointer->next = pos.pointer->next.pointer->next;
        rem.pointer->next = pos.pointer->next.pointer->next;
        pos.pointer->next.pointer->next = rem;
    }

    template <class T>
    static_list<T>::static_list(size_t s) : max_size(s), rest_begin(new node<T>[s]), before_begin_node(rest_begin) {}

    template <class T>
    static_list<T>::static_list(const static_list<T>& x) : max_size(x.max_size), rest_begin(new node<T>[max_size]), before_begin_node(rest_begin) {
        
    }
}
#endif