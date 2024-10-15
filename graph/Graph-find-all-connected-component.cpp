#include <iostream>
#include <vector>
#include <queue>
#include <utility>

"https://www.acmicpc.net/problem/11724"

using namespace std;

int main()
{
    int v_n, e_n;

    cin >> v_n >> e_n;

    vector<int> adj[v_n + 1];

    for(int i = 0; i < e_n; ++i)
    {
        int v1, v2;

        cin >> v1 >> v2;

        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }

    vector<bool> vis(v_n + 1, false);

    queue<int> q;
    int counter = 0;

    for(int i = 1; i <= v_n; ++i)
    {
        if(vis[i]) continue;

        q.push(i);

        while(!q.empty())
        {
            int cur_v = q.front(); q.pop();

            for(auto& next_v : adj[cur_v])
            {
                if(vis[next_v]) continue;

                q.push(next_v);
                
                vis[next_v] = true;
            }
        }
        counter++;
    }

    cout << counter << '\n';

    return 0;
}
