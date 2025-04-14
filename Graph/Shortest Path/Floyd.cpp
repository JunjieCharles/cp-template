#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P6175
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> e(n + 1, std::vector<int>(n + 1, -1));
    for (int i = 1; i <= n; i++)
    {
        e[i][i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        if (e[u][v] == -1 || w < e[u][v])
        {
            e[u][v] = w;
            e[v][u] = w;
        }
    }
    auto dis = e;
    int ans = -1;
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j && i != k && j != k && dis[i][j] != -1 && e[i][k] != -1 && e[k][j] != -1)
                {
                    if (ans == -1 || dis[i][j] + e[i][k] + e[k][j] < ans)
                    {
                        ans = dis[i][j] + e[i][k] + e[k][j];
                    }
                }
                if (dis[i][k] != -1 && dis[k][j] != -1)
                {
                    if (dis[i][j] == -1 || dis[i][j] > dis[i][k] + dis[k][j])
                    {
                        dis[i][j] = dis[i][k] + dis[k][j];
                    }
                }
            }
        }
    }
    if (ans == -1)
    {
        std::cout << "No solution.\n";
    }
    else
    {
        std::cout << ans << '\n';
    }
}