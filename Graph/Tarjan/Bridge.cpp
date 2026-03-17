#include <bits/stdc++.h>
using namespace std;

// https://www.luogu.com.cn/problem/P1656
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
	
	int clk = 1;
	vector<int> dfn(n + 1, -1), low(n + 1, -1);
	vector<pair<int, int>> bridges;
	auto dfs = [&](auto &dfs, int u, int f) -> void {
		dfn[u] = low[u] = clk++;
		for (int v : e[u]) {
			if (v == f) continue;
			if (dfn[v] == -1) {
				dfs(dfs, v, u);
				if (low[v] > dfn[u]) {
					bridges.push_back({min(u, v), max(u, v)});
				}
				low[u] = min(low[u], low[v]);
			} else {
				low[u] = min(low[u], dfn[v]);
			}
		}
	};
	dfs(dfs, 1, 0);
	
	sort(bridges.begin(), bridges.end());
	for (auto uv : bridges) {
		int u = uv.first;
		int v = uv.second;
		cout << u << ' ' << v << '\n';
	}
}
