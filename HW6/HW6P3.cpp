#include <iostream>
#include "../header/MyStack.h"

using namespace std;
int main()
{
    char temp, top;
    alan::stack<char> data(100);
    while (cin >> temp)
    {
        switch (temp)
        {
            case '(':
            case '[':
            case '{':
                data.push(temp);
                break;
            case ')':
                if (data.empty())
                {
                    cout << "no\n" << temp << "ÆÚ´ý×óÀ¨ºÅ\n";
                    goto endloop;
                }
                else if (top = data.pop(), top != '(')
                {
                    cout << "no\n" << top << "ÆÚ´ýÓÒÀ¨ºÅ\n";
                    goto endloop;
                }
                break;
            case ']':
                if (data.empty())
                {
                    cout << "no\n" << temp << "ÆÚ´ý×óÀ¨ºÅ\n";
                    goto endloop;
                }
                else if (top = data.pop(), top != '[')
                {
                    cout << "no\n" << top << "ÆÚ´ýÓÒÀ¨ºÅ\n";
                    goto endloop;
                }
                break;
            case '}':
                if (data.empty())
                {
                    cout << "no\n" << temp << "ÆÚ´ý×óÀ¨ºÅ\n";
                    goto endloop;
                }
                else if (top = data.pop(), top != '{')
                {
                    cout << "no\n" << top << "ÆÚ´ýÓÒÀ¨ºÅ\n";
                    goto endloop;
                }
                break;
        }
    }
    if (!data.empty()) 
    {
        cout << "no\n" << data.pop() << "ÆÚ´ýÓÒÀ¨ºÅ\n";
        goto endloop;
    }
    cout << "yes\n";
    endloop:;
}