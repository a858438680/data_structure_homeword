#include "../header/MyStack.h"
#include <iostream>
#include <cctype>
#include <map>
#include <functional>
#include <stdexcept>

using namespace std;
auto binops = map<char, function<int (int, int)>>{
    {'+', [](int i, int j){return i+j;}},
    {'-', [](int i, int j){return i-j;}},
    {'*', [](int i, int j){return i*j;}},
    {'/', [](int i, int j){if (j == 0) throw domain_error("ERROR\n"); return i/j;}}
};

char peeknext(istream& is)
{
    while (isspace(is.peek())) is.get();
    return is.peek();
}

inline bool isoperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

void calc_until_bracket(alan::stack<char>& ins, alan::stack<int>& num)
{
    char op;
    int i, j;
    while (op = ins.pop(), op != '(')
    {
        j = num.pop();
        i = num.pop();
        num.push(binops[op](i, j));
    }
}

void calc(alan::stack<char>& ins, alan::stack<int>& num)
{
    char op;
    int i, j;
    while (!ins.empty() && ins.peek() != '(')
    {
        op = ins.pop();
        j = num.pop();
        i = num.pop();
        num.push(binops[op](i, j));
    }
}

int main()
{
    try
    {
        alan::stack<char> ins(100);
        alan::stack<int> num(100);
        int temp;
        while (peeknext(cin) != '=')
        {
            if (isdigit(peeknext(cin)))
            {
                cin >> temp;
                num.push(temp);
                if (!ins.empty() && (ins.peek() == '*' || ins.peek() == '/'))
                {
                    calc(ins, num);
                }
            }
            else if (isoperator(peeknext(cin)))
            {
                char op;
                switch (op = cin.get())
                {
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case '(':
                        ins.push(op);
                        break;
                    case ')':
                        calc_until_bracket(ins, num);
                        if (!ins.empty() && (ins.peek() == '*' || ins.peek() == '/'))
                        {
                            calc(ins, num);
                        }
                        break;
                }
            }
            else throw invalid_argument("ERROR\n");
        }
        calc(ins, num);
        cout << num.pop() << endl;
    }
    catch (domain_error err)
    {
        cout << err.what();
    }
    catch (invalid_argument err)
    {
        cout << err.what();
    }
}