#include "../header/MyVec.h"
#include "../header/MyPoly.h"
#include <iostream>
#include <algorithm>

int main()
{
    size_t m, n, e_temp;
    int p_temp;
    alan::vector<pair> input1;
    alan::vector<pair> input2;
    std::cin >> m;
    for (size_t i = 0; i < m; ++i)
    {
        if (std::cin >> p_temp >> e_temp)
            input1.push_back(pair{p_temp, e_temp});
    }
    std::cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        if (std::cin >> p_temp >> e_temp)
            input2.push_back(pair{p_temp, e_temp});
    }
    auto poly1 = convert(input1);
    auto poly2 = convert(input2);
    auto poly = poly1 * poly2;
    for (size_t i = 0; i < poly.size; ++i)
    {
        if (poly.data[i]) std::cout << poly.data[i] << " " << i << std::endl;
    }
}