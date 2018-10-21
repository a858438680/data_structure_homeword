#include "../header/MyVec.h"
#include <vector>
#include <iostream>
#include <algorithm>

class pair {
public:
    int p;
    size_t e;
};

class poly {
public:
    std::vector<int> data;
    size_t greater_than_max_exponent;
};

poly operator+(poly lhs, poly rhs)
{
    auto new_greater_than_max_exponent = lhs.greater_than_max_exponent > rhs.greater_than_max_exponent ? lhs.greater_than_max_exponent : rhs.greater_than_max_exponent;
    auto lower_greater_than_max_exponent = lhs.greater_than_max_exponent < rhs.greater_than_max_exponent ? lhs.greater_than_max_exponent : rhs.greater_than_max_exponent;
    auto& lower = lhs.greater_than_max_exponent < rhs.greater_than_max_exponent ? lhs : rhs;
    for (size_t i = 0; i < new_greater_than_max_exponent - lower_greater_than_max_exponent; ++i)
    {
        lower.data.push_back(0);
    }
    std::vector<int> new_data;
    for (size_t i = 0; i < new_greater_than_max_exponent; ++i)
    {
        new_data.push_back(lhs.data[i] + rhs.data[i]);
    }
    return poly{std::move(new_data), new_greater_than_max_exponent};
}

poly convert(const std::vector<pair>& input)
{
    if (!input.empty())
    {
        auto itr = std::max_element(input.begin(), input.end(), [](pair lhs, pair rhs){return lhs.e < rhs.e;});
        auto greater_than_max_exponent = (*itr).e + 1;
        auto ret = std::vector<int>(greater_than_max_exponent, 0);
        for (auto &v: input) {
            ret[v.e] = ret[v.e] + v.p;
        }
        return poly{ret, greater_than_max_exponent};
    }
    else return poly{std::vector<int>(), 0};
}

int main()
{
    size_t m, n, e_temp;
    int p_temp;
    std::vector<pair> input1;
    std::vector<pair> input2;
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
    auto poly = poly1 + poly2;
    for (size_t i = 0; i < poly.greater_than_max_exponent; ++i)
    {
        if (poly.data[i]) std::cout << poly.data[i] << " " << i << std::endl;
    }
}