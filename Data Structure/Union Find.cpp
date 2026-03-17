#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> fa, siz;

    UnionFind(int n) : fa(n), siz(n, 1)
    {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int u)
    {
        return fa[u] == u ? u : fa[u] = find(fa[u]);
    }

    void merge(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (siz[u] > siz[v]) swap(u, v);
        fa[u] = v;
        siz[v] += siz[u];
    }
};

// https://www.luogu.com.cn/problem/P3367
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    UnionFind uf(n + 1);
    for (int i = 0; i < m; i++) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z == 1) {
            uf.merge(x, y);
        } else {
            if (uf.find(x) == uf.find(y)) {
                cout << "Y\n";
            } else {
                cout << "N\n";
            }
        }
    }
    return 0;
}
