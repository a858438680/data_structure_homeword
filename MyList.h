#include <limits>
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
    class forward_list {
        template <class U> friend void swap(forward_list<U>&, forward_list<U>&) noexcept;
    public:
        // 类型：
        typedef T                                                   value_type;
        typedef value_type&                                         reference;
        typedef const value_type&                                   const_reference;
        typedef node_iterator<T>                                    iterator;
        typedef const_node_iterator<T>                              const_iterator; 
        typedef size_t                                              size_type;
        typedef size_t                                              difference_type;
    
        // 构造/复制/销毁：
        forward_list();
        forward_list(const forward_list<T>& x);
        forward_list(forward_list<T>&&);
    
        ~forward_list();
        forward_list<T>& operator=(forward_list<T> x);
    
        // 迭代器：
        iterator                before_begin() noexcept;
        const_iterator          before_begin() const noexcept;
        iterator                begin() noexcept;
        const_iterator          begin() const noexcept;
        iterator                end() noexcept;
        const_iterator          end() const noexcept;
    
        // 容量：
        size_type max_size() const noexcept;
        bool      empty() const noexcept;
    
        // 元素访问：
        reference       front();
        const_reference front() const;
    
        // 修改器：
        template <class... Args> void emplace_front(Args&&... args);
    
        void push_front(const T& x);
        void push_front(T&& x);
        void pop_front();
    
        template <class... Args> 
            iterator emplace_after(iterator position, Args&&... args);
        iterator insert_after(iterator position, const T& x);
        iterator insert_after(iterator position, T&& x);
    
        iterator erase_after(iterator position);
        iterator erase_after(iterator position, iterator last);
        void clear() noexcept;
    
        // forward_list 操作：
        void splice_after(iterator position, forward_list<T>& x);
        void splice_after(iterator position, forward_list<T>&& x);
        void splice_after(iterator position, forward_list<T>& x,
                        iterator i);
        void splice_after(iterator position, forward_list<T>&& x,
                        iterator i);
        void splice_after(iterator position, forward_list<T>& x,
                        iterator first, iterator last);
        void splice_after(iterator position, forward_list<T>&& x,
                        iterator first, iterator last);
    
        void remove(const T& value);
        template <class Predicate> void remove_if(Predicate pred);
    
        void unique();
        template <class BinaryPredicate> void unique(BinaryPredicate binary_pred);
    
        void merge(forward_list<T>& x);
        void merge(forward_list<T>&& x);
        template <class Compare> void merge(forward_list<T>& x, Compare comp);
        template <class Compare> void merge(forward_list<T>&& x, Compare comp);
    
        void sort();
        template <class Compare> void sort(Compare comp);
        void reverse() noexcept;
    private:
        node<T> before_begin_node;
        static const iterator the_end_iterator;
        static const iterator& the_end()
        {
            return the_end_iterator;
        }
    };

    template <class T>
    void swap(forward_list<T>& lhs, forward_list<T>& rhs) noexcept
    {
        using std::swap;
        swap(rhs.before_begin_node, lhs.before_begin_node);
    }

    template <class T>
    const node_iterator<T> forward_list<T>::the_end_iterator(nullptr);

    template <class T>
    forward_list<T>::forward_list() : before_begin_node(nullptr) {}

    template <class T>
    forward_list<T>::forward_list(const forward_list<T>& x) : before_begin_node(nullptr)
    {
        auto rem = the_end();
        for (auto first = x.before_begin_node.next; first != the_end(); ++first)
        {
            auto itr = new node<T>(*first, nullptr);
            if (rem != the_end())
            {
                rem.pointer->next = itr;
                rem = itr;
            }
            else
            {
                before_begin_node.next = itr;
                rem = itr;
            }
        }
    } 

    template <class T>
    forward_list<T>::forward_list(forward_list<T>&& x) : before_begin_node(std::move(x.before_begin_node))
    {
        x.before_begin_node.next = nullptr; 
    }

    template <class T>
    forward_list<T>::~forward_list()
    {
        while (before_begin_node.next != the_end())
            delete (before_begin_node.next++).pointer;
    }

    template <class T>
    forward_list<T>& forward_list<T>::operator=(forward_list<T> x)
    {
        using std::swap;
        swap(x, *this);
        return *this;
    }

    template <class T>
    void forward_list<T>::push_front(const T& x)
    {
        before_begin_node.next = new node<T>(x, before_begin_node.next.pointer);
    }

    template <class T>
    void forward_list<T>::push_front(T&& x)
    {
        before_begin_node.next = new node<T>(std::move(x), before_begin_node.next.pointer);
    }

    template <class T>
    void forward_list<T>::pop_front()
    {
        auto new_head = before_begin_node.next.pointer->next;
        delete before_begin_node.next.pointer;
        before_begin_node.next = new_head;
    }

    template <class T>
    template <class... Args>
        node_iterator<T> forward_list<T>::emplace_after(iterator pos, Args&&... args)
        {
            pos.pointer->next = new node<T>(T(std::forward<Args>(args)...), pos.pointer->next);
            return ++pos;
        }
    
    template <class T>
    node_iterator<T> forward_list<T>::insert_after(iterator pos, const T& x)
    {
        pos.pointer->next = new node<T>(x, pos.pointer->next);
        return ++pos;
    }

    template <class T>
    node_iterator<T> forward_list<T>::insert_after(iterator pos, T&& x)
    {
        pos.pointer->next = new node<T>(std::move(x), pos.pointer->next);
        return ++pos;
    }

    template <class T>
    node_iterator<T> forward_list<T>::erase_after(iterator pos)
    {
        auto erase = pos.pointer->next.pointer;
        pos.pointer->next = pos.pointer->next.pointer->next;
        delete erase;
        return ++pos;
    }

    template <class T>
    node_iterator<T> forward_list<T>::erase_after(iterator first, iterator last)
    {
        auto pos = first;
        node<T>* rem;
        while (first != last)
        {
            rem = (++first).pointer->next;
            delete first.pointer;
        }
        pos.pointer->next = rem;
        return last;
    }

    template <class T>
    node_iterator<T> forward_list<T>::before_begin() noexcept
    {
        return iterator(&before_begin_node);
    }

    template <class T>
    const_node_iterator<T> forward_list<T>::before_begin() const noexcept
    {
        return const_iterator(&before_begin_node);
    }

    template <class T>
    node_iterator<T> forward_list<T>::begin() noexcept
    {
        return before_begin_node.next;
    }

    template <class T>
    const_node_iterator<T> forward_list<T>::begin() const noexcept
    {
        return before_begin_node.next;
    }

    template <class T>
    node_iterator<T> forward_list<T>::end() noexcept
    {
        return the_end();
    }

    template <class T>
    const_node_iterator<T> forward_list<T>::end() const noexcept
    {
        return the_end();
    }

    template <class T>
    T& forward_list<T>::front()
    {
        return *(before_begin_node.next);
    }

    template <class T>
    const T& forward_list<T>::front() const
    {
        return *(before_begin_node.next);
    }

    template <class T>
    bool forward_list<T>::empty() const noexcept
    {
        return before_begin_node.next == the_end();
    }

    template <class T>
    size_t forward_list<T>::max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max();
    }

    template <class T>
    void forward_list<T>::remove(const T& value)
    {
        auto pos = before_begin();
        while (pos.pointer->next)
        {
            if (*(pos.pointer->next) == value) erase_after(pos);
            else ++pos;
        }
    }

    template <class T>
    template <class Predicate> void forward_list<T>::remove_if(Predicate pred)
    {
        auto pos = before_begin();
        while (pos.pointer->next)
        {
            if (pred(*(pos.pointer->next))) erase_after(pos);
            else ++pos;
        }
    }

    template <class T>
    void forward_list<T>::merge(forward_list<T>& x)
    {
        auto itr1 = before_begin();
        auto itr2 = x.before_begin();
        for(; itr1.pointer->next && itr2.pointer->next; ++itr1, ++itr2)
        {
            if(*(itr2.pointer->next) < *(itr1.pointer->next))
            {
                auto rem = itr2.pointer->next.pointer->next;
                itr2.pointer->next.pointer->next = itr1.pointer->next;
                itr1.pointer->next = itr2.pointer->next;
                itr2.pointer->next = rem;
                ++itr2;
            }
            else ++itr1;
        }
    }

    template <class T>
    void forward_list<T>::sort()
    {
        
    }

    template <class T>
    void forward_list<T>::reverse() noexcept
    {
        auto rem_this = before_begin();
        auto rem_next = before_begin().pointer->next;
        while (rem_next)
        {
            auto temp = rem_next;
            rem_next = rem_next.pointer->next;
            temp.pointer->next = rem_this;
            rem_this = temp;
        }
        if (before_begin().pointer->next)
        {
            begin().pointer->next = nullptr;
            before_begin().pointer->next = rem_this;
        }
    }
}