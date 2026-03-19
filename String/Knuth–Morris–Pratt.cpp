#include <bits/stdc++.h>
using namespace std;

vector<int> kmp(const string &s)
{
	int n = (int)s.size();
	vector<int> p(n);
	for (int i = 1, j = 0; i < n; i++) {
		while (j > 0 && s[i] != s[j]) j = p[j - 1];
		if (s[i] == s[j]) j++;
		p[i] = j;
	}
	return p;
}

// https://www.luogu.com.cn/problem/P3375
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	string s, t;
	cin >> s >> t;
	int ns = (int)s.size();
	int nt = (int)t.size();
	auto p = kmp(t + "#" + s);
	for (int i = 0; i < ns; i++) {
		if (p[nt + 1 + i] == nt) {
			cout << i - nt + 2 << '\n';
		}
	}
	for (int i = 0; i < nt; i++) {
		cout << p[i] << ' ';
	}
}
