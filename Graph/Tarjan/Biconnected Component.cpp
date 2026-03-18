#include <bits/stdc++.h>
using namespace std;

// https://www.luogu.com.cn/problem/P8435
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> e(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	int clk = 0;
	vector<int> dfn(n + 1, -1), low(n + 1, -1);
	int nBcc = 0;
	vector<vector<int>> eBcc(n + 1);
	vector<int> st;
	st.reserve(n);
	auto dfs = [&](auto &dfs, int u, int f) -> void {
		dfn[u] = low[u] = ++clk;
		st.push_back(u);
		int son = 0;
		for (int v : e[u]) {
			if (v == f) continue;  
			if (dfn[v] == -1) {
				dfs(dfs, v, u);
				low[u] = min(low[u], low[v]);
				son++;
				if (low[v] >= dfn[u]) {
					nBcc++;
					eBcc.emplace_back();
					while (!st.empty()) {
						int p = st.back();
						st.pop_back();
						eBcc[p].push_back(n + nBcc);
						eBcc[n + nBcc].push_back(p);
						if (p == v) break;
					}
					eBcc[u].push_back(n + nBcc);
					eBcc[n + nBcc].push_back(u);
				}
			} else {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (f == -1 && son == 0) {
			nBcc++;
			eBcc.emplace_back();
			eBcc[u].push_back(n + nBcc);
			eBcc[n + nBcc].push_back(u);
		}
	};
	for (int u = 1; u <= n; u++) {
		if (dfn[u] == -1) {
			dfs(dfs, u, -1);
		}
	}
	
	cout << nBcc << '\n';
	for (int u = n + 1; u <= n + nBcc; u++) {
		cout << eBcc[u].size() << ' ';
		for (int v: eBcc[u]) {
			cout << v << ' ';
		}
		cout << '\n';
	}
}
