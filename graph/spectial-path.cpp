#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>
#include <deque>

//"https://www.acmicpc.net/problem/1504"

using namespace std;

vector<long long> Dijkstra(vector<vector<pair<long long, long long>>>& g, int st)
{
	vector<long long> dist(g.size(), (long long)1e10);

	priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;

	dist[st] = 0;
	pq.push({ 0, st });

	while (!pq.empty())
	{
		int start, w;

		tie(w, start) = pq.top(); pq.pop();

		if (dist[start] != w) continue;
		else
		{
			for (const auto& sToV : g[start])
			{
				int viaDis = dist[start] + sToV.first;

				if (viaDis < dist[sToV.second])
				{
					dist[sToV.second] = viaDis;

					pq.push({ viaDis, sToV.second });
				}
			}
		}
	}

	return dist;
}

int main()
{
	int n, m;

	cin >> n >> m;

	vector<vector<pair<long long, long long>>> g(n + 1);

	for (int i = 0; i < m; ++i)
	{
		int v1, v2, w;

		cin >> v1 >> v2 >> w;

		g[v1].push_back({ w, v2 });
		g[v2].push_back({ w, v1 });
	}

	int viaStart, viaDesti;

	cin >> viaStart >> viaDesti;

	auto dist1 = Dijkstra(g, 1);
	auto distViaSt = Dijkstra(g, viaStart);
	auto distViaDes = Dijkstra(g, viaDesti);

	long long p1 = dist1[viaStart] + distViaSt[viaDesti] + distViaDes[n];
	long long p2 = dist1[viaDesti] + distViaDes[viaStart] + distViaSt[n];

	long long result = min(p1, p2);

	cout << (result >= (long long)1e10 ? -1 : result);

	return 0;
}
