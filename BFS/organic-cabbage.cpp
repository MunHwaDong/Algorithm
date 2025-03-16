#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>
#include <stack>
#include <deque>

using namespace std;

//https://www.acmicpc.net/problem/1012

void BFS(vector<vector<int>>& map, int r, int c, int n, int m)
{
	int dr[4] = { 1, 0, -1, 0 };
	int dc[4] = { 0, 1, 0, -1 };

	queue<std::tuple<int, int>> q;

	q.push(tie(r, c));

	while (!q.empty())
	{
		int a, b;
		
		tie(a, b) = q.front(); q.pop();

		for (int i = 0; i < 4; ++i)
		{
			int nr = dr[i] + a;
			int nc = dc[i] + b;

			if (nr < 0 || nr >= n || nc < 0 || nc >= m)
				continue;

			if (map[nr][nc] != 1)
				continue;

			q.push(tie(nr, nc));
			map[nr][nc] = map[a][b] + 1;
		}
	}
}

int main()
{
	int t = 0;

	cin >> t;

	while (t--)
	{
		int n, m, k = 0;

		cin >> n >> m >> k;

		vector<vector<int>> map(n, vector<int>(m, -1));

		while (k--)
		{
			int r, c;

			cin >> r >> c;

			map[r][c] = 1;
		}

		// Do Somthing Here

		int counter = 0;

		for (int r = 0; r < n; ++r)
		{
			for (int c = 0; c < m; ++c)
			{
				if (map[r][c] == 1)
				{
					BFS(map, r, c, n, m);
					counter++;
				}
			}
		}

		cout << counter << endl;
	}

	return 0;
}
