#include "../header/MyVec.h"
#include "../header/MyPoly.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

int main()
{
    size_t m, e_temp;
    int p_temp;
    double x;
    alan::vector<pair> input;
    std::cin >> m;
    for (size_t i = 0; i < m; ++i)
    {
        if (std::cin >> p_temp >> e_temp)
            input.push_back(pair{p_temp, e_temp});
    }
    std::cin >> x;
    auto poly = convert(input);
    std::cout << std::fixed << std::setprecision(1) << poly.value(x) << std::endl;
}