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

// https://www.luogu.com.cn/problem/P3379
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, s;
    std::cin >> n >> m >> s;
    std::vector<std::vector<int>> e(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    std::vector<int> dfn(n + 1), fa(n + 1);
    int clk = 1;
    auto dfs = [&](auto &dfs, int u, int f) -> void
    {
        fa[u] = f;
        dfn[u] = clk++;
        for (int v : e[u])
        {
            if (v == f) continue;
            dfs(dfs, v, u);
        }
    };
    dfs(dfs, s, 0);
    std::vector<int> dfa(n + 1);
    for (int i = 1; i <= n; i++)
    {
        dfa[dfn[i]] = fa[i];
    }
    auto cmp = [&](int a, int b) { return dfn[a] < dfn[b]; };
    SparseTable<int, decltype(cmp)> st(dfa, cmp);
    auto lca = [&](int u, int v) -> int
    {
        if (u == v) return u;
        if (dfn[u] > dfn[v]) std::swap(u, v);
        return st.query(dfn[u] + 1, dfn[v]);
    };
    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;
        std::cout << lca(u, v) << "\n";
    }
}