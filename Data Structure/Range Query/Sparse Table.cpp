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

// https://www.luogu.com.cn/problem/P3865
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    SparseTable<int, greater<int>> st(n + 1);
    st.build(a);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r) << '\n';
    }
}
