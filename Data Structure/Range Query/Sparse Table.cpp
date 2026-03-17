#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Cmp = less<T>>
struct SparseTable {
    vector<vector<T>> v;
    Cmp cmp;

    SparseTable(int n, Cmp cmp = Cmp()) : cmp(cmp)
    {
        int K = __lg(n);  // n cannot be 0
        v.assign(K + 1, vector<T>(n));
    }

    void build(const vector<T> &a)
    {
        int n = a.size();
        int K = __lg(n);
        for (int i = 0; i < n; i++) {
            v[0][i] = a[i];
        }
        for (int k = 1; k <= K; k++) {
            for (int i = 0; i + (1 << k) - 1 < n; i++) {
                v[k][i] = min(v[k - 1][i], v[k - 1][i + (1 << (k - 1))], cmp);
            }
        }
    }

    T query(int l, int r) const
    {
        int k = __lg(r - l + 1);
        return min(v[k][l], v[k][r - (1 << k) + 1], cmp);
    }
};

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
    
    vector<int> dfn(n + 1), dfa(n + 1);
    int clk = 1;
    auto dfs = [&](auto &dfs, int u, int f) -> void {
        dfn[u] = clk++;
        dfa[dfn[u]] = f;
        for (int v : e[u]) {
            if (v == f) continue;
            dfs(dfs, v, u);
        }
    };
    dfs(dfs, s, 0);
    
    auto cmp = [&](int a, int b) { return dfn[a] < dfn[b]; };
    SparseTable<int, decltype(cmp)> st(n + 1, cmp);
    st.build(dfa);
    auto lca = [&](int u, int v) -> int {
        if (u == v) return u;
        if (dfn[u] > dfn[v]) swap(u, v);
        return st.query(dfn[u] + 1, dfn[v]);
    };
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
}
