#include <bits/stdc++.h>
using namespace std;

template <typename T>
std::vector<T> make_vector(size_t n, const T& val = T())
{
    return std::vector<T>(n, val);
}

template <typename T, typename... Args>
auto make_vector(size_t n, Args... args)
{
    auto inner = make_vector<T>(args...);
    return std::vector<decltype(inner)>(n, inner);
}

int main()
{
}
