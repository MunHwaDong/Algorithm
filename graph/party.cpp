#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <functional>

"https://www.acmicpc.net/problem/1238"

using namespace std;

void dijkstra(vector<vector<pair<int, int>>>& g, int start, int n, vector<int>& result)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    vector<int> dist(n + 1, int(1e9));

    dist[start] = 0;
    q.push({0, start});

    while(!q.empty())
    {
        pair<int, int> cur = q.top(); q.pop();

        if(dist[cur.second] != cur.first) continue;

        for(const auto& ele : g[cur.second])
        {
            int via = dist[cur.second] + ele.first;

            if(dist[ele.second] > via)
            {
                dist[ele.second] = via;
                q.push({via, ele.second});
            }
        }
    }
    
    result = dist;
}

int main()
{
    int n, m, x;

    cin >> n >> m >> x;

    vector<vector<pair<int, int>>> g(n + 1);

    for(int i = 0; i < m; ++i)
    {
        int v1, v2, w;

        cin >> v1 >> v2 >> w;

        g[v1].push_back({w, v2});
    }

    vector<vector<int>> table(n + 1, vector<int>(n + 1, int(1e9)));

    for(int i = 1; i <= n; ++i)
    {
        dijkstra(g, i, n, table[i]);
    }

    int result = 0;

    for(int i = 1; i <= n; ++i)
    {
        result = max(result, table[i][x] + table[x][i]);
    }

    cout << result;

    return 0;
}
