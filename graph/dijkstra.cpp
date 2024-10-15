#include <iostream>
#include <vector> // 가변 길이 배열
#include <list> //링크드 리스트 (Doubly Linked List)
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue> //우선순위큐 포함
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

using namespace std;

int main()
{
	int n, m; priority_queue<int> q;

	cin >> n >> m;

	vector<vector<pair<int, int>>> g(n + 1);

	for (int i = 0; i < m; ++i)
	{
		int v1, v2, w;

		cin >> v1 >> v2 >> w;

		g[v1].push_back({ v2, w });
	}

	//dijkstra
	int start = 0;

	cin >> start;

	vector<int> dist(n + 1, int(1e9));
	vector<bool> isdicision(n + 1, false);

	dist[start] = 0;
	isdicision[start] = true;

	bool isntfinished = true;

	//모든 배열이 다 채워질때까지
	while (isntfinished)
	{
		cout << start << endl;
		for (const auto& ele : g[start])
		{
			dist[ele.first] = min(dist[ele.first], ele.second + dist[start]);
		}

		int minIdx = 0;

		for (int idx = 1; idx <= n; ++idx)
		{
			if (isdicision[idx]) continue;
			if (dist[minIdx] > dist[idx])
			{
				minIdx = idx;
			}
		}

		isdicision[minIdx] = true;
		start = minIdx;

		for (int i = 1; i <= n; ++i)
		{
			if (isdicision[i] == false) break;
			else if (i >= n) isntfinished = false;
		}
	}

	for (const auto& ele : dist)
	{
		cout << ele << " ";
	}

	return 0;
}
