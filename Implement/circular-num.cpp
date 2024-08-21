#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n = 0, m = 0;

    cin >> n >> m;

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    int dir = 2;
    
    pair<int, int> cur = {0, 0};

    int counter = 2;

    vector<vector<int>> map(n, vector<int>(m, 0));

    map[cur.first][cur.second] = 1;

    for(int i = 1; i < n * m; ++i)
    {
        int nx = cur.first + dx[dir];
        int ny = cur.second + dy[dir];

        if(nx >= n || nx < 0 || ny >= m || ny < 0 || map[nx][ny] != 0)
        {
            dir = dir - 1;

            if(dir < 0) dir = 3;

            nx = cur.first + dx[dir];
            ny = cur.second + dy[dir];
        }

        map[nx][ny] = counter++;
        cur.first = nx;
        cur.second = ny;
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            cout << map[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}
