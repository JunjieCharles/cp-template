#include <bits/stdc++.h>
using namespace std;
using Edge = pair<int ,int>;

// https://www.luogu.com.cn/problem/P8436
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    
	int n, m;
	cin >> n >> m;
	vector<vector<Edge>> e(n + 1);
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		e[u].emplace_back(v, i);
		e[v].emplace_back(u, i);
	}
	
	int clk = 0, nEbcc = 0;
	vector<int> dfn(n + 1, -1), low(n + 1, -1);
	vector<int> ebcc(n + 1, -1);
	vector<int> st;
	st.reserve(n);
	auto dfs = [&](auto &dfs, int u, int from) -> void {
		dfn[u] = low[u] = ++clk;
		st.push_back(u);
		for (auto edge : e[u]) {
			int v = edge.first;
			int id = edge.second;
			if (id == from) continue;
			if (dfn[v] == -1) {
				dfs(dfs, v, id);
				low[u] = min(low[u], low[v]);
			} else {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (low[u] == dfn[u]) {
			nEbcc++;
			while (!st.empty()) {
				int v = st.back();
				st.pop_back();
				ebcc[v] = nEbcc;
				if (v == u) break;
			}
		}
	};
	for (int u = 1; u <= n; u++) {
		if (dfn[u] == -1) {
			dfs(dfs, u, -1);
		}
	}
	
	vector<vector<int>> ans(nEbcc + 1);
	for (int u = 1; u <= n; u++) {
		ans[ebcc[u]].push_back(u);
	}
	
	cout << nEbcc << '\n';
	for (int i = 1; i <= nEbcc; i++) {
		cout << ans[i].size() << ' ';
		for (int u : ans[i]) {
			cout << u << ' ';
		}
		cout << '\n';
	}
}
