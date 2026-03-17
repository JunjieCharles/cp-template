#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct SegmentTree {
    struct Node {
        T v = 0;
        T tmul = 1, tadd = 0;
        
        void apply(T mul, T add, int len)
        {
            v = v * mul + add * len;
            tadd = tadd * mul + add;
            tmul = tmul * mul;
        }
    };

    int n;
    vector<Node> tr;

    SegmentTree(int n) : n(n), tr((n + 1) << 2) {}

    void push_up(int p)
    {
        tr[p].v = tr[p << 1].v + tr[p << 1 | 1].v;
    }

    void push_down(int p, int l, int r)
    {
        int mid = (l + r) >> 1;
        tr[p << 1].apply(tr[p].tmul, tr[p].tadd, mid - l + 1);
        tr[p << 1 | 1].apply(tr[p].tmul, tr[p].tadd, r - mid);
        tr[p].tmul = 1;
        tr[p].tadd = 0;
    }

    void build(const vector<int>& a, int l, int r, int p = 1)
    {
        if (l == r) {
            tr[p].v = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(a, l, mid, p << 1);
        build(a, mid + 1, r, p << 1 | 1);
        push_up(p);
    }

    void update(int ql, int qr, T mul, T add, int l, int r, int p = 1)
    {
        if (ql <= l && r <= qr) {
            tr[p].apply(mul, add, r - l + 1);
            return;
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(ql, qr, mul, add, l, mid, p << 1);
        if (qr > mid)  update(ql, qr, mul, add, mid + 1, r, p << 1 | 1);
        push_up(p);
    }

    T query(int ql, int qr, int l, int r, int p = 1)
    {
        if (ql <= l && r <= qr) return tr[p].v;
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        T res = 0;
        if (ql <= mid) res = res + query(ql, qr, l, mid, p << 1);
        if (qr > mid)  res = res + query(ql, qr, mid + 1, r, p << 1 | 1);
        return res;
    }
};

// https://www.luogu.com.cn/problem/P3373
template <int MOD>
struct ModInt {
    int x;
    ModInt(int x = 0) : x(x) {}
    ModInt operator+(const ModInt &u) const { return x + u.x >= MOD ? x + u.x - MOD : x + u.x; }
    ModInt operator-(const ModInt &u) const { return x - u.x < 0 ? x - u.x + MOD : x - u.x; }
    ModInt operator*(const ModInt &u) const { return int(1ll * x * u.x % MOD); }
};

template <int MOD>
void run(int n, int q)
{
    SegmentTree<ModInt<MOD>> tr(n);
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    tr.build(a, 1, n);

    for (int i = 0; i < q; i++) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z == 1) {
            int k;
            cin >> k;
            tr.update(x, y, k, 0, 1, n);
        } else if (z == 2) {
            int k;
            cin >> k;
            tr.update(x, y, 1, k, 1, n);
        } else {
            cout << tr.query(x, y, 1, n).x << '\n';
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q, m;
    cin >> n >> q >> m;
    if (m == 38) run<38>(n, q);
    else run<571373>(n, q);
}
