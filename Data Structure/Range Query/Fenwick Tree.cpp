#include <bits/stdc++.h>

template <typename T>
struct FenwickTree
{
    int n;
    std::vector<T> v;

    FenwickTree(const int n) : n(n), v(n) {}

    void update(int p, const T add)
    {
        while (p < n)
        {
            v[p] += add;
            p += (p + 1) & -(p + 1);
        }
    }

    T query(int p) const
    {
        T re = 0;
        while (p >= 0)
        {
            re += v[p];
            p -= (p + 1) & -(p + 1);
        }
        return re;
    }

    T query(const int l, const int r) const
    { 
        return query(r) - query(l - 1);
    }
};

// https://www.luogu.com.cn/problem/P3374
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    FenwickTree<int> tr(n + 1);
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        tr.update(i + 1, x);
    }
    for (int i = 0; i < m; i++)
    {
        int z, x, y;
        std::cin >> z >> x >> y;
        if (z == 1)
        {
            tr.update(x, y);
        }
        else
        {
            std::cout << tr.query(x, y) << '\n';
        }
    }
}
