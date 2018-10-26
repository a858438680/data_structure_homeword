#include "../header/MyStack.h"
#include <iostream>
#include <stdexcept>

using namespace std;
int main()
{
    int temp;
    size_t cap;
    cin >> cap;
    auto data = alan::stack<int>(cap);
    string ins;
    while (cin >> ins)
    {
        try
        {
            if (ins[0] == 'q') break;
            else {
                switch (ins[1])
                {
                    case 'o' :
                        cout << data.pop() << endl;
                        break;
                    case 'u' :
                        cin >> temp;
                        data.push(temp);
                        break;
                    default :
                        throw invalid_argument("invalid_instruction\n");
                        break;
                }
            }
        }
        catch (stack_empty err)
        {
            cout << err.what();
        }
        catch (stack_full err)
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