#include <bits/stdc++.h>
using namespace std;

// https://www.luogu.com.cn/problem/P3387
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	vector<vector<int>> e(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
	}
	
	int clk = 0, nScc = 0;
	vector<int> dfn(n + 1, -1), low(n + 1, -1);
	vector<int> scc(n + 1, -1);
	vector<int> st;
	st.reserve(n);
	auto dfs = [&](auto &dfs, int u, int f) -> void {
		dfn[u] = low[u] = ++clk;
		st.push_back(u);
		for (int v : e[u]) {
			if (dfn[v] == -1) {
				dfs(dfs, v, u);
				low[u] = min(low[u], low[v]);
			} else if (scc[v] == -1) {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (low[u] == dfn[u]) {
			nScc++;
			while (!st.empty()) {
				int v = st.back();
				st.pop_back();
				scc[v] = nScc;
				if (v == u) break;
			}
		}
	};
	for (int u = 1; u <= n; u++) {
		if (dfn[u] == -1) {
			dfs(dfs, u, -1);
		}
	}
	
	vector<int> aScc(nScc + 1);
	vector<vector<int>> eScc(nScc + 1);
	for (int u = 1; u <= n; u++) {
		aScc[scc[u]] += a[u];
		for (int v : e[u]) {
			if (scc[u] != scc[v]) {
				eScc[scc[u]].push_back(scc[v]);
			}
		}
	}
	
	vector<int> dp(nScc + 1, -1);
	auto dfsScc = [&](auto &dfsScc, int u) -> int {
		if (dp[u] != -1) return dp[u];
		int res = 0;
		for (int v : eScc[u]) {
			int dv = dfsScc(dfsScc, v);
			res = max(res, dv);
		}
		return dp[u] = res + aScc[u];
	};
	int ans = 0;
	for (int u = 1; u <= nScc; u++) {
		int du = dfsScc(dfsScc, u);
		ans = max(ans, du);
	}
	cout << ans << '\n';
}
