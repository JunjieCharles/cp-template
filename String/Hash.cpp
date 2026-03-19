#include <bits/stdc++.h>
using namespace std;
constexpr int P = 233;
constexpr int M = 1004535809;

template <int M>
struct Mint {
    int x;
    Mint(int x = 0) : x(x) {}
    Mint operator+(const Mint &u) const { return x + u.x >= M ? x + u.x - M : x + u.x; }
    Mint operator-(const Mint &u) const { return x - u.x < 0 ? x - u.x + M : x - u.x; }
    Mint operator*(const Mint &u) const { return (int)(1ll * x * u.x % M); }
    explicit operator int() const { return x; }
};

template <int P, int M>
struct Hash {
	int n;
	static vector<Mint<M>> powP;
    vector<Mint<M>> h;

    Hash(const string &s) : n((int)s.size()), h(n)
    {
        while ((int)powP.size() <= n) {
            powP.push_back(powP.back() * P);
        }
        for (int i = 0; i < n; i++) {
            powP[i + 1] = powP[i] * P;
            h[i] = (i == 0) ? s[i] : h[i - 1] * P + s[i];
        }
    }

    Mint<M> query(int l = -1, int r = -1) const
    {
    	if (l == -1 && r == -1) return h[n - 1];
        if (l == 0) return h[r];
        return h[r] - h[l - 1] * powP[r - l + 1];
    }
};

template <int P, int M>
vector<Mint<M>> Hash<P, M>::powP{1};

// https://www.luogu.com.cn/problem/P3370
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	cin >> n;
	unordered_set<int> hashs;
	for (int i = 0 ; i < n; i++) {
		string s;
		cin >> s;
		Hash<P, M> h(s);
		hashs.insert((int)h.query());
	}
	cout << hashs.size() << '\n';
}
