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

"https://www.acmicpc.net/problem/7576"

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

    int n = 0, m = 0;

    cin >> m >> n;

    vector<vector<int>> map(n, vector<int>(m, 0));

    vector<vector<int>> v(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            cin >> map[i][j];
            if(map[i][j] == 1)
            {
                v[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    int dayCount = 0;

    // for(int i = 0; i < n; ++i)
    // {
    //     for(int j = 0; j < m; ++j)
    //     {
    //         if(map[i][j] == 1)
    //         {
    //             v[i][j] = 1;
    //             q.push({i, j});
    //         }
    //     }
    // }

    while(!q.empty())
    {
        pair<int, int> cur = q.front(); q.pop();

        for(int dir = 0; dir < 4; ++dir)
        {
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];

            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(v[nx][ny] != -1 || map[nx][ny] != 0) continue;

            v[nx][ny] = v[cur.first][cur.second] + 1;
            dayCount = max(v[nx][ny], dayCount);
            q.push({nx, ny});
        }
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(map[i][j] == 0 && v[i][j] == -1)
            {
                dayCount = -1;
            }
        }
    }

    cout << dayCount;

    // while (t--)
    // {

    // }


    return 0;
}
