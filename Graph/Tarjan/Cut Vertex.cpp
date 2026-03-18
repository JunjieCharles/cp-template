#include <bits/stdc++.h>
using namespace std;

// https://www.luogu.com.cn/problem/P3388
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
	vector<int> isCut(n + 1);
	auto dfs = [&](auto &dfs, int u, int f) -> void {
		dfn[u] = low[u] = clk++;
		int son = 0;
		for (int v : e[u]) {
			if (v == f) continue;  
			if (dfn[v] == -1) {
				dfs(dfs, v, u);
				if (f != -1 && low[v] >= dfn[u]) {
					isCut[u] = 1;
				}
				low[u] = min(low[u], low[v]);
				son++;
			} else {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (f == -1 && son > 1) {
			isCut[u] = 1;
		}
	};
	for (int u = 1; u <= n; u++) {
		if (dfn[u] == -1) {
			dfs(dfs, u, -1);
		}
	}
	
	int ans = accumulate(isCut.begin(), isCut.end(), 0);
	cout << ans << '\n';
	for (int u = 1; u <= n; u++) {
		if (isCut[u]) {
			cout << u << ' ';
		}
	}
}
