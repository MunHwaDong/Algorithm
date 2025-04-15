#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <map>
#include <stack>

//https://www.acmicpc.net/problem/2589

using namespace std;

void solved(vector<vector<char>>& ma, int n, int m)
{
    queue<pair<int, int>> q;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    int result = 0;

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(ma[i][j] == 'W')
                continue;

            q.push(make_pair(i, j));

            vector<vector<bool>> vis(n, vector<bool>(m, false));
            vector<vector<int>> minDist(n, vector<int>(m, 0));

            vis[i][j] = true;

            while(!q.empty())
            {
                int curr, curc = 0;

                tie(curr, curc) = q.front(); q.pop();

                for(int dir = 0; dir < 4; ++dir)
                {
                    int nr = curr + dr[dir];
                    int nc = curc + dc[dir];

                    if(nr < 0 || nc < 0 || nr >= n || nc >= m)
                        continue;
                    if(vis[nr][nc] || ma[nr][nc] == 'W')
                        continue;
                    
                    vis[nr][nc] = true;
                    minDist[nr][nc] = minDist[curr][curc] + 1;

                    q.push(make_pair(nr, nc));

                    if(minDist[nr][nc] > result)
                        result = minDist[nr][nc];
                }
            }
        }
    }

    cout << result;
}

int main()
{

    int n, m = 0;

    cin >> n >> m;

    vector<vector<char>> ma(n, vector<char>(m, 0));

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            cin >> ma[i][j];
        }
    }

    solved(ma, n, m);

    return 0;
}
