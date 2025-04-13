#include <bits/stdc++.h>

template <typename T>
struct BinarySearchTree
{
    struct Node
    {
        T v;
        int cnt = 1, siz = 1, lson = -1, rson = -1;

        Node(T x) : v(x) {}
    };

    std::vector<Node> nodes;
    int root = -1;

    int siz(int u) const { return u == -1 ? 0 : nodes[u].siz; }
    void maintain(int u) { nodes[u].siz = siz(nodes[u].lson) + siz(nodes[u].rson) + nodes[u].cnt; }

    int newnode(T x)
    {
        nodes.push_back(Node(x));
        return nodes.size() - 1;
    }

    int find(T x) const
    {
        int p = root;
        while (p != -1 && x != nodes[p].v)
        {
            if (x < nodes[p].v) p = nodes[p].lson;
            else p = nodes[p].rson;
        }
        return p;
    }

    int pre(T x) const
    {
        int p = root, res = -1;
        while (p != -1)
        {
            if (x > nodes[p].v) res = p, p = nodes[p].rson;
            else p = nodes[p].lson;
        }
        return res;
    }

    int nxt(T x) const
    {
        int p = root, res = -1;
        while (p != -1)
        {
            if (x < nodes[p].v) res = p, p = nodes[p].lson;
            else p = nodes[p].rson;
        }
        return res;
    }

    int rank(T x) const
    {
        int p = root, k = 1;
        while (p != -1)
        {
            if (nodes[p].v == x) return siz(nodes[p].lson) + k;
            if (nodes[p].v > x) p = nodes[p].lson;
            else k += siz(p) - siz(nodes[p].rson), p = nodes[p].rson;
        }
        return k;
    }

    int kth(int k) const
    {
        if (siz(root) < k) return -1;
        int p = root;
        while (p != -1)
        {
            if (nodes[p].lson != -1 && k <= siz(nodes[p].lson))
                p = nodes[p].lson;
            else if (nodes[p].rson != -1 && k > siz(p) - siz(nodes[p].rson))
                k -= siz(p) - siz(nodes[p].rson), p = nodes[p].rson;
            else break;
        }
        return p;
    }
};

template <typename T>
struct Treap : BinarySearchTree<T>
{
    using BinarySearchTree<T>::nodes, BinarySearchTree<T>::root,
          BinarySearchTree<T>::siz, BinarySearchTree<T>::maintain,
          BinarySearchTree<T>::newnode, BinarySearchTree<T>::find,
          BinarySearchTree<T>::pre, BinarySearchTree<T>::nxt,
          BinarySearchTree<T>::rank, BinarySearchTree<T>::kth;

    std::mt19937 rnd;

    Treap() : rnd(0) {}

    bool check(int u, int v) { return int(rnd() % (siz(u) + siz(v))) < siz(u); }

    std::pair<int, int> split(int u, T x)
    {
        if (u == -1) return {-1, -1};
        if (nodes[u].v > x)
        {
            const auto [r1, r2] = split(nodes[u].lson, x);
            nodes[u].lson = r2;
            maintain(u);
            return {r1, u};
        }
        else
        {
            const auto [r1, r2] = split(nodes[u].rson, x);
            nodes[u].rson = r1;
            maintain(u);
            return {u, r2};
        }
    }

    int merge(int u, int v)
    {
        if (u == -1) return v;
        if (v == -1) return u;
        if (check(u, v))
        {
            nodes[u].rson = merge(nodes[u].rson, v);
            maintain(u);
            return u;
        }
        else
        {
            nodes[v].lson = merge(u, nodes[v].lson);
            maintain(v);
            return v;
        }
    }

    void insert(T x)
    {
        auto [u1, u2] = split(root, x - 1);
        auto [v1, v2] = split(u2, x);
        if (v1 == -1) v1 = merge(v1, newnode(x));
        else nodes[v1].cnt++, maintain(v1);
        u2 = merge(v1, v2);
        root = merge(u1, u2);
    }

    void erase(T x)
    {
        auto [u1, u2] = split(root, x - 1);
        auto [v1, v2] = split(u2, x);
        if (v1 == -1) return;
        nodes[v1].cnt--;
        maintain(v1);
        if (!nodes[v1].cnt) v1 = -1;
        u2 = merge(v1, v2);
        root = merge(u1, u2);
    }
};


// https://www.luogu.com.cn/problem/P3369
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    Treap<int> tr;
    for (int i = 0; i < n; i++)
    {
        int o, x;
        std::cin >> o >> x;
        if (o == 1)
        {
            tr.insert(x);
        }
        else if (o == 2)
        {
            tr.erase(x);
        }
        else if (o == 3)
        {
            std::cout << tr.rank(x) << "\n";
        }
        else if (o == 4)
        {
            std::cout << tr.nodes[tr.kth(x)].v << "\n";
        }
        else if (o == 5)
        {
            std::cout << tr.nodes[tr.pre(x)].v << "\n";
        }
        else if (o == 6)
        {
            std::cout << tr.nodes[tr.nxt(x)].v << "\n";
        }
    }
}