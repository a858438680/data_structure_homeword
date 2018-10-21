#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include "../header/MyVec.h"

class stack_empty {
public:
    explicit stack_empty(size_t i): count(i) {}
    size_t count;
};

class stack_full {
public:
    explicit stack_full(size_t i): count(i) {}
    size_t count;
};

class illegal{ 
public:
    illegal() {}
};

class stack_empty_n_full{
public:
    stack_empty_n_full(size_t i, size_t j): empty_count(i), full_count(j){}
    size_t empty_count;
    size_t full_count;
};

class illegal_n_full{
public:
    explicit illegal_n_full(size_t i): count(i) {}
    size_t count;
};

class col {
    friend void display(const col& x);
public:
    explicit col(size_t s): cap(s), size(0), arr(new int[s]) {}
    
    col(const col& x):cap(x.cap), size(x.size), arr(new int[x.cap]) //copy constructor
    {
        for (size_t i = 0; i < x.cap; ++i)
        {
            *(arr+i) = *(x.arr+i);
        }
    }

    col(col&& x):cap(x.cap), size(x.size), arr(x.arr) //move constructor;
    {
        x.arr = nullptr;
    }

    col& operator=(col x) //copy and swap
    {
        auto temp_cap = x.cap;
        auto temp_arr = x.arr;
        x.cap = cap;
        x.arr = arr;
        cap = temp_cap;
        arr = temp_arr;
        return *this;
    }

    ~col() {delete arr;}

    bool empty() const {return size == 0;}

    bool full() const {return size == cap;}

    void push(int x) {
        if (size == cap) throw std::out_of_range("full");
        else *(arr + (size++)) = x;
    }

    int pop() {
        if (size == 0) throw std::out_of_range("empty");
        else return *(arr + (--size));
    }

    int peek() const {
        if (size == 0) throw std::out_of_range("empty");
        else return *(arr + size - 1);
    }

private:
    size_t cap;
    size_t size;
    int *arr;
};

int move(alan::vector<col>& cols, size_t lhs, size_t rhs) {
    try {
        if (!cols[lhs].empty() && !cols[rhs].empty() && cols[lhs].peek() > cols[rhs].peek()) throw std::invalid_argument("illegal");
        cols[rhs].push(cols[lhs].pop());
        return cols[rhs].peek();
    }
    catch (std::out_of_range err)
    {
        if (!std::strcmp(err.what(), "empty"))
        {   
            try {
                cols[rhs].push(0);
                cols[rhs].pop();
                throw stack_empty(lhs);
            }
            catch (std::out_of_range err_full)
            {
                throw stack_empty_n_full(lhs, rhs);
            }
        }
        else if (!std::strcmp(err.what(), "full"))
        {
            throw stack_full(rhs);
        }
    }
    catch (std::invalid_argument err)
    {
        try {
            cols[rhs].push(0);
            cols[rhs].pop();
            throw illegal();
        }
        catch (std::out_of_range err_full)
        {
            throw illegal_n_full(rhs);
        }
    }
    return 0; //Ensure that the function has a return value though it will never be used. Otherwise you will get a warning.
}

void display(const col& x) {
    if (x.empty()) std::cout << 0 << std::endl;
    else
    {
        for (size_t i = x.size; i > 0; --i)
        {
            std::cout << *(x.arr + i - 1) << " ";
        }
        std::cout << std::endl;
    }
}

enum class instruct {
    move,
    display,
    quit
};

using namespace std;

instruct read_instruct(istream& is)
{
    string ins;
    is >> ins;
    if (ins == "QUIT") return instruct::quit;
    else if (ins == "MOVE") return instruct::move;
    else if (ins == "DISPLAY") return instruct::display;
    else throw std::invalid_argument("parse_error");
}

int main()
{
    size_t n, k, temp;
    cin >> n >> k;
    alan::vector<col> cols;
    for (size_t i = 0; i < n; ++i)
    {
        if (cin >> temp && temp > 0) cols.push_back(col(temp));
    }
    for (size_t i = 0; i < k; ++i)
    {
        int temp;
        if (cin >> temp) cols[0].push(temp);
    }
    instruct ins;
    while(ins = read_instruct(std::cin), ins != instruct::quit)
    {
        try {
            switch (ins) {
                case instruct::move:
                    int lhs, rhs;
                    cin >> lhs >> rhs;
                    cout << move(cols, lhs-1, rhs-1) << endl;
                    break;
                case instruct::display:
                    int index;
                    cin >> index;
                    display(cols[index-1]);
                    break;
            }
        }
        catch (stack_empty err) {cout << err.count+1 << " IS EMPTY\n";}
        catch (stack_full err) {cout << err.count+1 << " IS FULL\n";}
        catch (illegal err) {cout << "ILLEGAL\n";}
        catch (stack_empty_n_full err) {cout << err.empty_count+1 << " IS EMPTY\n" << err.full_count+1 << " IS FULL\n";}
        catch (illegal_n_full err) {cout << err.count+1 << " IS FULL\n" << "ILLEGAL\n";}
    }
    for (auto &v: cols) display(v);

    return 0;
}