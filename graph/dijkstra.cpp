#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    int n, m;

    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n + 1);

    for(int i = 0; i < m; ++i)
    {
        int v1, v2, w;

        cin >> v1 >> v2 >> w;

        g[v1].push_back({v2, w});
    }

    //dijkstra

    int start = 0;

    cin >> start;

    vector<int> dist(n + 1, int(1e9));
    vector<bool> dicision(n + 1, false);

    dist[start] = 0;
    dicision[start] = true;
    bool isntFinished = true;

    while(isntFinished)
    {
        for(const auto& ele : g[start])
        {
            dist[ele.first] = min(dist[ele.first], dist[start] + ele.second);
        }

        int minIdx = 0;

        for(int i = 1; i <= n; ++i)
        {
            if(dicision[i]) continue;
            if(dist[minIdx] > dist[i])
            {
                minIdx = i;
            }
        }

        dicision[minIdx] = true;
        start = minIdx;

        for(int i = 1; i <= n; ++i)
        {
            if(!dicision[i]) break;
            else if(i >= n) isntFinished = false;
        }

    }

    for(const auto& ele : dist)
    {
        cout << ele << " ";
    }

    return 0;
}
