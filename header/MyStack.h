#ifndef _MY_STACK_H
#define _MY_STACK_H
#include <cstddef>
#include <stdexcept>

struct stack_full {
    const char *what() { return "Stack is Full\n"; }
};

struct stack_empty {
    const char *what() { return "Stack is Empty\n"; }
};

namespace alan
{
    template <class T>
    class stack {
    public:
        explicit stack(size_t s): cap(s), size(0), arr(new T[s]) {}
        
        stack(const stack& x):cap(x.cap), size(x.size), arr(new T[x.cap]) //copy constructor
        {
            for (size_t i = 0; i < x.cap; ++i)
            {
                *(arr+i) = *(x.arr+i);
            }
        }

        stack(stack&& x):cap(x.cap), size(x.size), arr(x.arr) //move constructor;
        {
            x.arr = nullptr;
        }

        stack& operator=(stack x) //copy and swap
        {
            auto temp_cap = x.cap;
            auto temp_arr = x.arr;
            x.cap = cap;
            x.arr = arr;
            cap = temp_cap;
            arr = temp_arr;
            return *this;
        }

        ~stack() {delete[] arr;}

        bool empty() const {return size == 0;}

        bool full() const {return size == cap;}

        void push(T x) {
            if (size == cap) throw stack_full();
            else *(arr + (size++)) = x;
        }

        T pop() {
            if (size == 0) throw stack_empty();
            else return *(arr + (--size));
        }

        T peek() const {
            if (size == 0) throw stack_empty();
            else return *(arr + size - 1);
        }

    private:
        size_t cap;
        size_t size;
        T *arr;
    };
}
#endif