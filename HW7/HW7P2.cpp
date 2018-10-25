#include <iostream>
#include <string>
#include <stdexcept>
 
struct deque_full {
    const char *what() { return "Queue is Full\n"; }
};
 
struct deque_empty {
    const char *what() { return "Queue is Empty\n"; }
};

struct node {
    int value;
    node *pre;
    node *next;
};
 
class deque {
public:
    deque(size_t s): size(0), cap(s), before_head{0, nullptr, nullptr}, after_tail{0, nullptr, nullptr}
    {
        before_head.next = &after_tail;
        after_tail.pre = &before_head;
    }
    deque(const deque& x): size(x.size), cap(x.cap), before_head{0, nullptr, nullptr}, after_tail{0, nullptr, nullptr}
    {
        before_head.next = &after_tail;
        after_tail.pre = &before_head;
        auto ptr = x.before_head.next;
        auto before_ptr = &before_head;
        while (ptr != &(x.after_tail))
        {
            before_ptr = before_ptr->next = before_ptr->next->pre = new node{ptr->value, before_ptr, before_ptr->next};
            ptr = ptr->next;
        }
    }
    deque(deque&& x): size(x.size), cap(x.cap), before_head{0, nullptr, nullptr}, after_tail{0, nullptr, nullptr}
    {
        before_head.next = &after_tail;
        after_tail.pre = &before_head;
        if (!x.empty())
        {
            before_head.next = x.before_head.next;
            after_tail.pre = x.after_tail.pre;
            x.before_head.next = &(x.after_tail);
            x.after_tail.pre = &(x.before_head);
            x.size = 0;
        }
    }
    ~deque()
    {
        auto ptr = before_head.next;
        while(ptr != &after_tail)
        {
            auto rem = ptr->next;
            delete ptr;
            ptr = rem;
        }
    }
    deque& operator=(deque rhs)
    {
        using std::swap;
        swap(*this, rhs);
        return *this;
    }
    bool empty() { return size == 0; }
    bool full() { return size == cap; }
    void push(int x)
    {
        if (!full())
        {
            after_tail.pre = after_tail.pre->next = new node{x, after_tail.pre, &after_tail};
            ++size;
        }
        else throw deque_full();
    }
    int pop()
    {
        if (!empty())
        {
            auto ret = before_head.next->value;
            before_head.next = before_head.next->next;
            delete before_head.next->pre;
            before_head.next->pre = &before_head;
            --size;
            return ret;
        }
        else throw deque_empty();
    }
private:
    size_t size;
    size_t cap;
    node before_head;
    node after_tail;
};
 
using namespace std;
int main()
{
    int temp;
    size_t cap;
    cin >> cap;
    auto data = deque(cap);
    string ins;
    while (cin >> ins)
    {
        try
        {
            if (ins[0] == 'q') break;
            else {
                switch (ins[0])
                {
                    case 'd' :
                        cout << data.pop() << endl;
                        break;
                    case 'e' :
                        cin >> temp;
                        data.push(temp);
                        break;
                    default :
                        throw invalid_argument("invalid_instruction\n");
                        break;
                }
            }
        }
        catch (deque_empty err)
        {
            cout << err.what();
        }
        catch (deque_full err)
        {
            cout << err.what();
        }
    }
    while (!data.empty())
    {
        cout << data.pop() << ' ';
    }
    cout << endl;
}