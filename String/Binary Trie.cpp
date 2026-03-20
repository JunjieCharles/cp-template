#include <bits/stdc++.h>
using namespace std;
using Edge = pair<int, unsigned>;

template <int W = 31, typename T = unsigned>
struct BinTrie {
	vector<array<int, 2>> e;
	vector<T> val;
	
	BinTrie()
	{
		e.push_back({-1, -1});
		val.push_back(0);
	}

	void insert(unsigned x)
	{
		int u = 0;
		for (int j = W - 1; j >= 0; j--) {
			unsigned i = (x >> j) & 1u;
			if (e[u][i] == -1) {
				e.push_back({-1, -1});
				val.push_back(0);
				e[u][i] = (int)e.size() - 1;
			}
			u = e[u][i];
		}
		val[u] = x;
	}
	
	T query(unsigned x) const
	{
		int u = 0;
		for (int j = W - 1; j >= 0; j--) {
			unsigned i = (x >> j) & 1u;
			if (e[u][i ^ 1] != -1) u = e[u][i ^ 1];
			else if (e[u][i] != -1) u = e[u][i];
			else break;
		}
		return val[u];
	}
};

// https://www.luogu.com.cn/problem/P4551
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	cin >> n;
	vector<vector<Edge>> e(n + 1);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		unsigned w;
		cin >> u >> v >> w;
		e[u].emplace_back(v, w);
		e[v].emplace_back(u, w);
	}
	
	vector<unsigned> val(n + 1);
	auto dfs = [&](auto &dfs, int u, int f, unsigned fw) -> void {
		val[u] = val[f] ^ fw;
		for (auto edge : e[u]) {
			int v = edge.first;
			unsigned w = edge.second;
			if (v == f) continue;
			dfs(dfs, v, u, w);
		}
	};
	dfs(dfs, 1, 0, 0);
	
	BinTrie<31> tr;
	unsigned ans = 0;
	for (int i = 1; i <= n; i++) {
		unsigned qs = tr.query(val[i]);
		ans = max(ans, val[i] ^ qs);
		tr.insert(val[i]);
	}
	
	cout << ans << '\n';
	return 0;
}
