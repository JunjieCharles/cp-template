#include <bits/stdc++.h>
using namespace std;

template <char C = 'a', int S = 26>
struct Trie {
	vector<vector<int>> e;
	vector<int> val;
	
	Trie() : e(1, vector<int>(S, -1)), val(1) {}

	void insert(const string &s)
	{
		int u = 0;
		for (char c : s) {
			int i = c - C;
			if (e[u][i] == -1) {
				e.emplace_back(S, -1);
				val.push_back(0);
				e[u][i] = (int)e.size() - 1;
			}
			u = e[u][i];
			val[u]++;
		}
	}
	
	int query(const string &s) const
	{
		int u = 0;
		for (char c : s) {
			int i = c - C;
			if (e[u][i] == -1) return 0;
			u = e[u][i];
		}
		return val[u];
	}
};

// https://www.luogu.com.cn/problem/P8306
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		int n, q;
		cin >> n >> q;
		Trie<0, 128> tr;
		for (int i = 0; i < n; i++) {
			string s;
			cin >> s;
			tr.insert(s);
		}
		for (int i = 0 ;i < q; i++) {
			string s;
			cin >> s;
			cout << tr.query(s) << '\n';
		}
	}
}
