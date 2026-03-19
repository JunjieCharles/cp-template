#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(42);

template <typename T>
struct Treap {
    struct Node {
        T v;
        int cnt = 1, siz = 1, lson = -1, rson = -1;
        unsigned int pri;
        
        Node(T x) : v(x), pri(rnd()) {}
    };

    vector<Node> nodes;
    int root = -1;

    Treap(int n) { nodes.reserve(n); }
    inline int siz(int u) const { return u == -1 ? 0 : nodes[u].siz; }
    inline void maintain(int u) { nodes[u].siz = siz(nodes[u].lson) + siz(nodes[u].rson) + nodes[u].cnt; }

    int newnode(T x)
    {
        nodes.push_back(Node(x));
        return nodes.size() - 1;
    }

    void split(int u, T x, int &l, int &r)
    {
        if (u == -1) {
            l = r = -1;
            return;
        }
        if (nodes[u].v > x) {
            split(nodes[u].lson, x, l, nodes[u].lson);
            r = u;
        } else {
            split(nodes[u].rson, x, nodes[u].rson, r);
            l = u;
        }
        maintain(u);
    }

    int merge(int u, int v)
    {
        if (u == -1) return v;
        if (v == -1) return u;
        if (nodes[u].pri > nodes[v].pri) {
            nodes[u].rson = merge(nodes[u].rson, v);
            maintain(u);
            return u;
        } else {
            nodes[v].lson = merge(u, nodes[v].lson);
            maintain(v);
            return v;
        }
    }

    void insert(T x)
    {
        int u1, u2, v1, v2;
        split(root, x - 1, u1, u2);
        split(u2, x, v1, v2);
        if (v1 == -1) {
            v1 = newnode(x);
        } else {
            nodes[v1].cnt++;
            maintain(v1);
        }
        root = merge(merge(u1, v1), v2);
    }

    void erase(T x)
    {
        int u1, u2, v1, v2;
        split(root, x - 1, u1, u2);
        split(u2, x, v1, v2);
        if (v1 != -1) {
            nodes[v1].cnt--;
            maintain(v1);
            if (!nodes[v1].cnt) v1 = -1;
        }
        root = merge(merge(u1, v1), v2);
    }

    int pre(T x) const
    {
        int p = root, res = -1;
        while (p != -1) {
            if (x > nodes[p].v) {
            	res = p;
            	p = nodes[p].rson;
        	} else {
        		p = nodes[p].lson;
    		}
        }
        return res;
    }

    int nxt(T x) const
    {
        int p = root, res = -1;
        while (p != -1) {
            if (x < nodes[p].v) {
            	res = p;
            	p = nodes[p].lson;
        	} else {
            	p = nodes[p].rson;
        	}
        }
        return res;
    }

    int rank(T x) const
    {
        int p = root, k = 1;
        while (p != -1) {
            if (nodes[p].v == x) return siz(nodes[p].lson) + k;
            if (nodes[p].v > x) {
            	p = nodes[p].lson;
        	} else {
        		k += siz(p) - siz(nodes[p].rson);
        		p = nodes[p].rson;
    		}
        }
        return k;
    }

    int kth(int k) const
    {
        if (siz(root) < k) return -1;
        int p = root;
        while (p != -1) {
            if (nodes[p].lson != -1 && k <= siz(nodes[p].lson)) {
                p = nodes[p].lson;
            } else if (nodes[p].rson != -1 && k > siz(p) - siz(nodes[p].rson)) {
                k -= siz(p) - siz(nodes[p].rson);
                p = nodes[p].rson;
            } else {
                break;
            }
        }
        return p;
    }
};

// https://www.luogu.com.cn/problem/P3369
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    Treap<int> tr(n);
    for (int i = 0; i < n; i++) {
        int o, x;
        cin >> o >> x;
        if (o == 1) {
            tr.insert(x);
        } else if (o == 2) {
            tr.erase(x);
        } else if (o == 3) {
            cout << tr.rank(x) << "\n";
        } else if (o == 4) {
            cout << tr.nodes[tr.kth(x)].v << "\n";
        } else if (o == 5) {
            cout << tr.nodes[tr.pre(x)].v << "\n";
        } else if (o == 6) {
            cout << tr.nodes[tr.nxt(x)].v << "\n";
        }
    }
}
