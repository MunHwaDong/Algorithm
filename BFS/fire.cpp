#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstring>
#include <iomanip>
#include <numeric>

using namespace std;

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void solve(string str)
{

}

int main()
{
    fastIO();

    int t = 1; // 테스트 케이스가 여러 개인 경우 입력받아 사용
    // cin >> t; // 테스트 케이스 입력받는 경우 주석 해제

    // while(--t)
    // {

    // }
    /*
        1. 불은 한 턴마다 상하좌우로 번진다. -> 번짐으로써 지훈이가 갈 수 있는 길도 매 턴마다 달라진다.
        2. 지훈이도 한 턴마다 상하좌우로 움직일 수 있다.
        3. 각 칸에 불이 몇 턴에 번지는지를 먼저 맵에 bfs를 돌려 저장한다.
        4. 지훈이의 탈출로를 bfs를 통해 찾는데 bfs의 조건에 해당 턴에 불이 붙는지를 비교하는 조건문을 추가한다
    
    */

    int n = 0, m = 0;

    cin >> n >> m;

    vector<string> map(n);
    pair<int, int> jihunPos;

    vector<vector<int>> jihunV(n, vector<int>(m, 0));
    queue<pair<int, int>> q;

    vector<vector<int>> fireV(n, vector<int>(m, 0));
    bool flag = false;

    int step = 0;

    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    cin.ignore();

    for(int i = 0; i < n; ++i)
    {
        getline(cin, map[i]);
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(map[i][j] == 'J') jihunPos = {i, j};
            else if(map[i][j] == 'F')
            {
                fireV[i][j] = 1;
                q.push({i, j});
            }
        }
    }

    while(!q.empty())
    {
        pair<int, int> cur = q.front(); q.pop();

        for(int dir = 0; dir < 4; ++dir)
        {
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];

            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(fireV[nx][ny] != 0 || map[nx][ny] == '#') continue;

            fireV[nx][ny] = fireV[cur.first][cur.second] + 1;
            q.push({nx, ny});
        }
    }

    q.push(jihunPos);
    jihunV[jihunPos.first][jihunPos.second] = 1;

    while(!q.empty())
    {
        pair<int, int> cur = q.front(); q.pop();

        for(int dir = 0; dir < 4; ++dir)
        {
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];

            //탈출!
            if(nx < 0 || nx >= n || ny < 0 || ny >= m)
            {
                step = jihunV[cur.first][cur.second];
                flag = true;
                
                while(!q.empty())
                {
                    q.pop();
                }
                break;
            }
            if(jihunV[nx][ny] != 0 || map[nx][ny] == '#') continue;

            //해당 턴에 불이 번져있는지?, 불이 그곳에 도달했었는지도 체크해야한다.
            if(((jihunV[cur.first][cur.second] + 1) >= fireV[nx][ny]) && fireV[nx][ny] != 0) continue;

            jihunV[nx][ny] = jihunV[cur.first][cur.second] + 1;
            q.push({nx, ny});
        }
    }

    (flag) ? cout << step : cout << "IMPOSSIBLE";

    return 0;
}
