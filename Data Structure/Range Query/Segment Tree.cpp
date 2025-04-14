#include <bits/stdc++.h>

template <typename T>
struct SegmentTree
{
    struct Node
    {
        int l, r;
        int lson = -1, rson = -1;
        T v;
        T tmul = 1, tadd = 0;

        Node(int i = 0, T x = 0) : l(i), r(i), v(x) {}
        Node(int l, int r, T x) : l(l), r(r), v(x) {}

        void update(T mul, T add)
        {
            v = v * mul + add * (r - l + 1);
            tadd = tadd * mul + add;
            tmul = tmul * mul;
        }
    };

    std::vector<Node> tr;

    SegmentTree(int l, int r) : tr(1, Node(l, r, 0))
    {
        tr.reserve((r - l + 1) << 2);
    }

    void push_down(int i)
    {
        if (tr[i].lson == -1)
        {
            int mid = (tr[i].l + tr[i].r) >> 1;
            tr[i].lson = (int)tr.size();
            tr.emplace_back(tr[i].l, mid, 0);
            tr[i].rson = (int)tr.size();
            tr.emplace_back(mid + 1, tr[i].r, 0);
        }
        tr[tr[i].lson].update(tr[i].tmul, tr[i].tadd);
        tr[tr[i].rson].update(tr[i].tmul, tr[i].tadd);
        tr[i].tadd = 0;
        tr[i].tmul = 1;
    }

    void update(int l, int r, T mul, T add, int i = 0)
    {
        if (tr[i].r < l || tr[i].l > r) return;
        if (tr[i].l < tr[i].r) push_down(i);
        if (l <= tr[i].l && r >= tr[i].r)
        {
            tr[i].update(mul, add);
            return;
        }
        update(l, r, mul, add, tr[i].lson);
        update(l, r, mul, add, tr[i].rson);
        tr[i].v = tr[tr[i].lson].v + tr[tr[i].rson].v;
    }

    T query(int l, int r, int i = 0)
    {
        if (tr[i].r < l || tr[i].l > r) return 0;
        if (tr[i].l < tr[i].r) push_down(i);
        if (l <= tr[i].l && r >= tr[i].r) return tr[i].v;
        return query(l, r, tr[i].lson) + query(l, r, tr[i].rson);
    }
};

// https://www.luogu.com.cn/problem/P3373
template <int MOD>
struct ModInt
{
    int x;

    ModInt(int x = 0) : x(x % MOD) {}

    ModInt operator+(const ModInt &u) const { return ModInt((x + u.x) % MOD); }
    ModInt operator-(const ModInt &u) const { return ModInt((x - u.x + MOD) % MOD); }
    ModInt operator*(const ModInt &u) const { return ModInt(1ll * x * u.x % MOD); }
};

template <int MOD>
void run(int n, int q)
{
    SegmentTree<ModInt<MOD>> tr(1, n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        std::cin >> x;
        tr.update(i, i, 1, x);
    }
    for (int i = 0; i < q; i++)
    {
        int z, x, y;
        std::cin >> z >> x >> y;
        if (z == 1)
        {
            int k;
            std::cin >> k;
            tr.update(x, y, k, 0);
        }
        else if (z == 2)
        {
            int k;
            std::cin >> k;
            tr.update(x, y, 1, k);
        }
        else
        {
            std::cout << tr.query(x, y).x << '\n';
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q, m;
    std::cin >> n >> q >> m;
    if (m == 38) run<38>(n, q);
    else run<571373>(n, q);
}