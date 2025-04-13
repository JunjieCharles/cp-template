#include <bits/stdc++.h>

struct UnionFind
{
    std::vector<int> f, siz;

    UnionFind(int n) : f(n), siz(n, 1)
    {
        std::iota(f.begin(), f.end(), 0);
    }

    int find(int u)
    {
        return f[u] == u ? u : f[u] = find(f[u]);
    }

    void merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if (fu == fv) return;
        if (siz[fu] > siz[fv]) std::swap(fu, fv);
        f[fu] = fv;
        siz[fv] += siz[fu];
    }
};

// https://www.luogu.com.cn/problem/P3367
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    UnionFind uf(n + 1);
    for (int i = 0; i < m; i++)
    {
        int z, x, y;
        std::cin >> z >> x >> y;
        if (z == 1)
        {
            uf.merge(x, y);
        }
        else
        {
            if (uf.find(x) == uf.find(y))
            {
                std::cout << "Y\n";
            }
            else
            {
                std::cout << "N\n";
            }
        }
    }
}