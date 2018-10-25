#include <iostream>
#include <string>
#include <stdexcept>
 
struct deque_full {
    const char *what() { return "Queue is Full\n"; }
};
 
struct deque_empty {
    const char *what() { return "Queue is Empty\n"; }
};
 
class deque {
public:
    deque(size_t s): size(0), cap(s), arr(new int[s]), head(arr) {}
    deque(const deque& x): size(x.size), cap(x.cap), arr(new int[x.cap]), head(x.head - x.arr + arr)
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
    void push(int x)
    {
        if (!full())
        {
            *(arr + (head - arr + size) % cap) = x;
            ++size;
        }
        else throw deque_full();
    }
    int pop()
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
private:
    size_t size;
    size_t cap;
    int *arr;
    int *head;
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