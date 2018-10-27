//#include "../header/MyQueue.h"
//#include "../header/MyStack.h"
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
            if (empty()) throw deque_empty();
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
#include <iostream>
#include <cassert>
using namespace std;
int main()
{
    char temp;
    alan::deque<char> entry(200);
    while ((temp = cin.get()) != '\n')
    {
        entry.push(temp);
    }
    alan::stack<char> station(200);
    while (cin.peek() != EOF)
    {
        try
        {
            auto entry_copy = entry;
            while ((temp = cin.get()) != '\n' && temp != EOF)
            {
                if (!entry_copy.empty() && entry_copy.peek() == temp) entry_copy.pop();
                else if (!station.empty() && station.peek() == temp) station.pop();
                else
                {
                    while (entry_copy.peek() != temp) station.push(entry_copy.pop());
                    entry_copy.pop();
                }
            }
            cout << "yes\n";
        }
        catch (alan::deque_empty err)
        {
            cout << "no\n";
            while ((temp = cin.get()) != '\n' && temp != EOF);
            while (!station.empty()) station.pop();
        }
    }
    assert(cin.get() == EOF);
}