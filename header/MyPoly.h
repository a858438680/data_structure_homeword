#include "MyVec.h"
#include <algorithm>

class pair {
public:
    int p;
    size_t e;
};

class poly {
public:
    double value(double x);
    alan::vector<int> data;
    size_t size;
};

double poly::value(double x)
{
    double ret = 0.0;
    for (auto itr = data.begin() + size; itr != data.begin(); --itr) ret = ret * x + *(itr - 1);
    return ret;
}

poly operator+(const poly& lhs, const poly& rhs)
{
    auto new_size = lhs.size > rhs.size ? lhs.size : rhs.size;
    auto lower_size = lhs.size < rhs.size ? lhs.size : rhs.size;
    auto& greater = lhs.size > rhs.size ? lhs : rhs;
    auto new_data = alan::vector<int>();
    for (size_t i = 0; i < lower_size; ++i)
    {
        new_data.push_back(lhs.data[i] + rhs.data[i]);
    }
    for (size_t i = lower_size; i < new_size; ++i)
    {
        new_data.push_back(greater.data[i]);
    }
    return poly{std::move(new_data), new_size};
}

poly operator*(const poly& lhs, const poly& rhs)
{
    auto new_size = lhs.size + rhs.size - 1;
    auto new_data = alan::vector<int>(new_size, 0);
    for (size_t i = 0; i < lhs.size; ++i)
        for (size_t j = 0; j < rhs.size; ++j)
        {
            new_data[i+j] = new_data[i+j] + lhs.data[i]*rhs.data[j];
        }
    return poly{std::move(new_data), new_size};
}

poly convert(const alan::vector<pair>& input)
{
    if (!input.empty())
    {
        auto itr = std::max_element(input.begin(), input.end(), [](pair lhs, pair rhs){return lhs.e < rhs.e;});
        auto size = (*itr).e + 1;
        auto ret = alan::vector<int>(size, 0);
        for (auto &v: input) {
            ret[v.e] = ret[v.e] + v.p;
        }
        return poly{ret, size};
    }
    else return poly{alan::vector<int>(), 0};
}