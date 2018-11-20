#include "../header/MyStack.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <stdexcept>

struct general_number {
    int num;
};

std::ostream& operator<<(std::ostream& os, general_number n)
{
    if (n.num < 10) return (os << n.num);
    else return (os << static_cast<char>(n.num-10+0x41));
}

int pow(int num, int exp)
{
    auto ret = 1;
    for (int i = 0; i < exp; i++)
    {
        ret *= num;
    }
    return ret;
}

int tonum(char c)
{
    if (isdigit(c)) return c-0x30;
    else if (isupper(c)) return 10 + c-0x41;
    else if (islower(c)) return 10 + c-0x61;
    else throw std::invalid_argument("not digit\n");
}

using namespace std;
int main()
{
    int origin_base, new_base, num = 0;
    string num_str;
    cin >> origin_base >> new_base >> num_str;
    auto itr = find_if(num_str.begin(), num_str.end(), [](char c){return c!='0';});
    auto valid_str = string(itr, num_str.end());
    for (size_t i = 0; i < valid_str.size(); ++i)
    {
        num += tonum(valid_str[i]) * pow(origin_base, valid_str.size() - 1 - i);
    }
    alan::stack<int> data(100);
    while (num)
    {
        data.push(num%new_base);
        num /= new_base;
    }
    while (!data.empty())
    {
        cout << general_number{data.pop()};
    }
    cout << endl;
    return 0;
}
