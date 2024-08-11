#include <iostream>
#include <vector> // 가변 길이 배열
#include <list> //링크드 리스트 (Doubly Linked List)
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstring>
#include <iomanip>
#include <numeric>

#define X first
#define Y second

using namespace std;

"https://www.acmicpc.net/problem/1926"

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void solve(string in)
{

}

int main()
{
    fastIO();

    int t = 1; // 테스트 케이스가 여러 개인 경우 입력받아 사용
    // cin >> t; // 테스트 케이스 입력받는 경우 주석 해제

    //while (t--)
    //{
    //}

    int n = 0, m = 0;

    cin >> n >> m;

    vector<vector<int>> map(n, vector<int>(m, 0));
    vector<vector<bool>> v(n, vector<bool>(m, 0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }

    int dx[4] = { 1, 0, -1, 0 };
    int dy[4] = { 0, 1, 0, -1 };

    int paintCount = 0;
    int maxArea = 0;
    int area = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            if (map[row][col] != 1) continue;

            //방문 했다는 것은 이미 어딘가에 붙어 있는 그림 영역이기 때문
            if (v[row][col] != 0) continue;

            queue<pair<int, int>> q;
            v[row][col] = 1;
            q.push({ row, col });
            paintCount++;
            area++;

            while (!q.empty())
            {
                pair<int, int> ele = q.front(); q.pop();

                for (int dir = 0; dir < 4; dir++)
                {
                    int nx = ele.X + dx[dir];
                    int ny = ele.Y + dy[dir];

                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (v[nx][ny] != 0 || map[nx][ny] != 1) continue;

                    v[nx][ny] = 1;
                    q.push({ nx, ny });
                    ++area;
                }
            }
            maxArea = max(maxArea, area);
            area = 0;
        }
    }

    cout << paintCount << '\n' << maxArea;

    return 0;
}
