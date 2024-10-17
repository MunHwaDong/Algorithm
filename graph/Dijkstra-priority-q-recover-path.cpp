#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <stack>
#include <functional>

#define weight first
#define vertex second
#define INF int(1e9)

"https://www.acmicpc.net/problem/11779"

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, start;

    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n + 1);

    for(int i = 0; i < m; ++i)
    {
        int v1, v2, w;

        cin >> v1 >> v2 >> w;

        g[v1].push_back({w, v2});
    }

    int depature, arrive;

    cin >> depature >> arrive;

    start = depature;

    //dijkstra
    auto comp = [](pair<int, int> a, pair<int, int> b) {return a > b;};

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> q(comp);

    vector<int> dist(n + 1, INF);
    vector<int> path(n + 1, 0);

    dist[start] = 0;
    path[start] = start;
    q.push({0, start});

    while(!q.empty())
    {
        pair<int, int> start = q.top(); q.pop();

        if(dist[start.vertex] != start.weight) continue;

        for(const auto& ele : g[start.vertex])
        {
            int viaDis = ele.weight + dist[start.vertex];

            if(dist[ele.vertex] > viaDis)
            {
                dist[ele.vertex] = viaDis;
                path[ele.vertex] = start.vertex;
                q.push({viaDis, ele.vertex});
            }
        }
    }
    int recover = arrive;
    stack<int> p;
    p.push(arrive);

    while(recover != depature)
    {
        recover = path[recover];
        p.push(recover);
    }

    cout << dist[arrive] << '\n' << p.size() << '\n';

    while(!p.empty())
    {
        cout << p.top() << " ";
        p.pop();
    }

    return 0;
}
