#include <bits/stdc++.h>

template <typename T, typename Cmp = std::less<T>>
struct SparseTable
{
    std::vector<std::vector<T>> v;
    Cmp cmp;

    SparseTable(const std::vector<T> &a, Cmp cmp = Cmp()) : v(a.size()), cmp(cmp)
    {
        int n = a.size();
        int K = std::bit_width(unsigned(n)) - 1;
        for (int i = 0; i < n; i++)
        {
            v[i].resize(K + 1);
            v[i][0] = a[i];
        }
        for (int k = 1; k <= K; k++)
        {
            for (int i = 0; i + (1 << k) - 1 < n; i++)
            {
                v[i][k] = std::min(v[i][k - 1], v[i + (1 << (k - 1))][k - 1], cmp);
            }
        }
    }

    T query(int l, int r) const
    {
        int k = std::bit_width(unsigned(r - l + 1)) - 1;
        return std::min(v[l][k], v[r - (1 << k) + 1][k], cmp);
    }
};

//https://www.luogu.com.cn/problem/P3865
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    SparseTable<int, std::greater<int>> st(a);
    for (int i = 0; i < m; i++)
    {
        int l, r;
        std::cin >> l >> r;
        std::cout << st.query(l - 1, r - 1) << '\n';
    }
}