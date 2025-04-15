#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <map>
#include <stack>

//https://www.acmicpc.net/problem/10026

using namespace std;

void BFS(vector<vector<char>>& m, vector<vector<bool>>& vis, pair<int, int> st, int n, bool isSakYak);

void solved(int n, vector<vector<char>>& m)
{
    vector<vector<bool>> vis(n, vector<bool>(n, false));

    std::map<char, int> cnt {
        {'R', 0},
        {'G', 0},
        {'B', 0}
    };

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(vis[i][j] == false)
            {
                cnt[m[i][j]] += 1;
                BFS(m, vis, make_pair(i, j), n, false);
            }
        }
    }
    
    cout << cnt['R'] + cnt['G'] + cnt['B'] << " ";

    cnt['R'] = 0;
    cnt['G'] = 0;
    cnt['B'] = 0;

    for(auto& row : vis)
        fill(row.begin(), row.end(), false);

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(vis[i][j] == false)
            {
                cnt[m[i][j]] += 1;
                BFS(m, vis, make_pair(i, j), n, true);
            }
        }
    }

    cout << cnt['R'] + cnt['G'] + cnt['B'] << "\n";
}

void BFS(vector<vector<char>>& m, vector<vector<bool>>& vis, pair<int, int> st, int n, bool isSakYak)
{
    queue<pair<int, int>> q;
    q.push(st);

    const char stColor = m[st.first][st.second];

    vis[st.first][st.second] = true;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    while(!q.empty())
    {
        int curr, curc = 0;

        tie(curr, curc) = q.front(); q.pop();

        for(int i = 0; i < 4; ++i)
        {
            int nr = curr + dr[i];
            int nc = curc + dc[i];

            if(nr < 0 || nc < 0 || nr >= n || nc >= n)
                continue;

            if(vis[nr][nc])
                continue;

            if(m[nr][nc] != stColor)
            {
                if(isSakYak && ((stColor == 'R' && m[nr][nc] == 'G') ||
                    (stColor == 'G' && m[nr][nc] == 'R')))
                {
                    q.push(make_pair(nr, nc));
                    vis[nr][nc] = true;
                }
                else
                    continue;
            }

            q.push(make_pair(nr, nc));
            vis[nr][nc] = true;
        }
    }
}

int main()
{
    int n = 0;
    
    cin >> n;

    vector<vector<char>> map(n, vector<char>(n, 0));

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            cin >> map[i][j];
        }
    }

    solved(n, map);

    return 0;
}
