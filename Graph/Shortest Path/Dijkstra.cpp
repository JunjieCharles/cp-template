#include <bits/stdc++.h>
using namespace std;
using T = long long;
using Edge = pair<int, T>;
using State = pair<T, int>;

// https://www.luogu.com.cn/problem/P4779
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<Edge>> e(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v; T w;
        cin >> u >> v >> w;
        e[u].emplace_back(v, w);
    }
    
    vector<T> dis(n + 1, -1);
    auto dijkstra = [&](int s) -> void {
        dis[s] = 0;
        priority_queue<State, vector<State>, greater<State>> q;
        q.emplace(0, s);
        
        while (!q.empty()) {
            T d; int u;
            tie(d, u) = q.top();
            q.pop();
            if (d > dis[u]) continue;
            
            for (auto &edge : e[u]) {
            	int v = edge.first;
            	T w = edge.second;
                if (dis[v] == -1 || dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    q.emplace(dis[v], v);
                }
            }
        }
    };
    dijkstra(s);
    
    for (int i = 1; i <= n; ++i) {
        cout << dis[i] << " \n"[i == n];
    }
}
