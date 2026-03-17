#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct FenwickTree {
    int n;
    vector<T> v;

    FenwickTree(int n) : n(n), v(n) {}

    void build(const vector<T>& a)
    {
        for (int i = 0; i < n; i++) {
        	v[i] += a[i];
            int j = i | (i + 1); 
            if (j < n) v[j] += v[i];
        }
    }

    void update(int p, const T add)
    {
        for (; p < n; p |= p + 1) {
            v[p] += add;
        }
    }

    T query(int p) const
    {
        T re = 0;
        for (; p >= 0; p = (p & (p + 1)) - 1) {
            re += v[p];
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    FenwickTree<long long> tr(n + 1);
    tr.build(a);
    for (int i = 0; i < m; i++) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z == 1) {
            tr.update(x, y);
        } else {
            cout << tr.query(x, y) << '\n';
        }
    }
}
