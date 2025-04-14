#include <bits/stdc++.h>

using T = long long;

// https://www.luogu.com.cn/problem/P4779
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, s;
    std::cin >> n >> m >> s;
    std::vector<std::vector<std::pair<int, T>>> e(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int u, v; T w;
        std::cin >> u >> v >> w;
        e[u].emplace_back(v, w);
    }
    std::vector<T> dis(n + 1, -1);
    auto dijkstra = [&](int s) -> void
    {
        dis[s] = 0;
        std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<>> q;
        q.emplace(0, s);
        while (!q.empty())
        {
            auto [x, u] = q.top();
            q.pop();
            if (x > dis[u]) continue;
            for (auto [v, w] : e[u])
            {
                if (dis[v] == -1 || dis[u] + w < dis[v])
                {
                    dis[v] = dis[u] + w;
                    q.emplace(dis[v], v);
                }
            }
        }
    };
    dijkstra(s);
    for (int i = 1; i <= n; ++i)
    {
        std::cout << dis[i] << " ";
    }
}