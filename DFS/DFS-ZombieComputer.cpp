#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>
#include <stack>
#include <deque>

//"https://www.acmicpc.net/problem/2606"

using namespace std;

int main()
{
	int n = 0, m = 0;

	cin >> n >> m;

	vector<vector<int>> g(n + 1);

	for (int i = 0; i < m; ++i)
	{
		int v1, v2;

		cin >> v1 >> v2;

		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}

	stack<int> s;

	vector<bool> vis(n + 1, false);

	int result = -1;

	s.push(1);
	vis[0] = true;
	vis[1] = true;

	while (!s.empty())
	{
		int v = s.top(); s.pop();
		result++;

		for (const auto& neigh : g[v])
		{
			if (vis[neigh] != true)
			{
				vis[neigh] = true;
				s.push(neigh);
			}
		}
	}

	cout << result;

	return 0;
}
