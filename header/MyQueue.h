#ifndef _MY_QUEUE_H
#define _MY_QUEUE_H
#include <stdexcept>

namespace alan
{
    struct deque_full {
        const char *what() { return "Queue is Full\n"; }
    };

    struct deque_empty {
        const char *what() { return "Queue is Empty\n"; }
    };
    
    template <class T>
    class deque {
    public:
        typedef T                                                   value_type;
        typedef value_type&                                         reference;
        typedef const value_type&                                   const_reference;
        typedef value_type*                                         iterator;
        typedef const value_type*                                   const_iterator; 
        typedef size_t                                              size_type;
        typedef size_t                                              difference_type;
        deque(size_t s): size(0), cap(s), arr(new T[s]), head(arr) {}
        deque(const deque& x): size(x.size), cap(x.cap), arr(new T[x.cap]), head(x.head - x.arr + arr)
        {
            for (size_t i = 0; i < cap; ++i)
            {
                arr[i] = x.arr[i];
            }
        }
        deque(deque&& x): size(x.size), cap(x.cap), arr(x.arr), head(x.head)
        {
            x.arr = nullptr;
        }
        ~deque()
        {
            delete[] arr;
        }
        deque& operator=(deque rhs)
        {
            using std::swap;
            swap(*this, rhs);
            return *this;
        }
        bool empty() { return size == 0; }
        bool full() { return size == cap; }
        void push(T x)
        {
            if (!full())
            {
                *(arr + (head - arr + size) % cap) = x;
                ++size;
            }
            else throw deque_full();
        }
        T pop()
        {
            if (!empty())
            {
                auto ret = *head;
                head = arr + (head - arr + 1) % cap;
                --size;
                return ret;
            }
            else throw deque_empty();
        }
        T peek()
        {
            return *head;
        }
    private:
        size_t size;
        size_t cap;
        T *arr;
        T *head;
    };
}
#endif