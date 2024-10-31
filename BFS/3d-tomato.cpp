#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>

//"https://www.acmicpc.net/problem/7569"

using namespace std;

int main()
{
	int m, n, h;

	cin >> m >> n >> h;

	int count = m * n * h;
	int well = 0;
	int bad = 0;
	int result = 0;

	int dx[6] = { 0, 0, -1, 0, 1, 0 };
	int dy[6] = { 0, 0, 0, 1, 0, -1 };
	int dz[6] = { -1, 1, 0, 0, 0, 0 };

	vector<vector<vector<int>>> box(h, vector<vector<int>>(n, vector<int>(m, 0)));
	queue<tuple<int, int, int>> tomato;

	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			for (int k = 0; k < m; ++k)
			{
				cin >> box[i][j][k];

				if (box[i][j][k] == 1)
				{
					tomato.push(tie( i, j, k ));
					count--;
					well++;
				}
				else if (box[i][j][k] == -1)
				{
					count--;
					bad++;
				}
			}
		}
	}

	while (!tomato.empty())
	{
		int curx, cury, curz;

		tie(curz, curx, cury) = tomato.front(); tomato.pop();

		for (int dir = 0; dir < 6; ++dir)
		{
			int nx = curx + dx[dir];
			int ny = cury + dy[dir];
			int nz = curz + dz[dir];

			if (nx < 0 || nx >= n|| ny < 0 || ny >= m || nz < 0 || nz >= h) continue;
			if (box[nz][nx][ny] != 0) continue;

			box[nz][nx][ny] = box[curz][curx][cury] + 1;
			count--;
			result = max(result, box[nz][nx][ny]);
			tomato.push(tie(nz, nx, ny));
		}
	}

	if (count > 0)
	{
		cout << -1;
	}
	else
	{
		if (m * n * h == well + bad)
		{
			cout << 0;
		}
		else
		{
			cout << result - 1;
		}
	}

	return 0;
}
