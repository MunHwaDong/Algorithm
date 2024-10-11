#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <algorithm>

"https://www.acmicpc.net/problem/1260"

using namespace std;

void dfs(vector<int> adj[], vector<bool>& vis, int start_v)
{
    stack<int> s;

    s.push(start_v);

    while(!s.empty())
    {
        int cur_v = s.top(); s.pop();

        if(vis[cur_v]) continue;

        cout << cur_v << " ";

        vis[cur_v] = true;

        for(int i = adj[cur_v].size(); i > 0; --i)
        {
            if(vis[adj[cur_v][i - 1]]) continue;

            s.push(adj[cur_v][i - 1]);
        }
    }

    cout << '\n';
}

void bfs(vector<int> adj[], vector<bool>& vis, int start_v)
{
    queue<int> q;

    q.push(start_v);
    vis[start_v] = true;

    while(!q.empty())
    {
        int cur_v = q.front(); q.pop();

        cout << cur_v << " ";

        for(auto& u : adj[cur_v])
        {
            if(vis[u]) continue;

            q.push(u);

            vis[u] = true;
        }
    }
    cout << '\n';
}

int main()
{
    int v_n, e_n, start_v;

    cin >> v_n >> e_n >> start_v;

    vector<int> adj[v_n + 1];
    vector<bool> vis(v_n + 1, false);

    for(int i = 0; i < e_n; ++i)
    {
        int v_1, v_2;

        cin >> v_1 >> v_2;

        adj[v_1].push_back(v_2);
        adj[v_2].push_back(v_1);
    }

    for(auto& ele : adj)
    {
        sort(ele.begin(), ele.end());
    }

    dfs(adj, vis, start_v);

    vector<bool> vis2(v_n + 1, false);
        
    bfs(adj, vis2, start_v);

    return 0;
}
