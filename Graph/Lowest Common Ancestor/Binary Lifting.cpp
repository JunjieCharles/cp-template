#include <bits/stdc++.h>
using namespace std;

// https://www.luogu.com.cn/problem/P3379
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int>> e(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    int k = __lg(n);
    vector<int> dep(n + 1, 0);
    vector<vector<int>> fa(n + 1, vector<int>(k + 1));
    auto dfs = [&](auto &dfs, int u, int p) -> void {
        fa[u][0] = p;
        dep[u] = dep[p] + 1;
        for (int i = 1; i <= k; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (int v : e[u]) {
            if (v == p) continue;
            dfs(dfs, v, u);
        }
    };
    dfs(dfs, s, 0);
    
    auto lca = [&](int u, int v) -> int {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = k; i >= 0; i--) {
            if (dep[fa[u][i]] >= dep[v]) {
                u = fa[u][i];
            }
        }
        if (u == v) return u;
        for (int i = k; i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    };
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
}
