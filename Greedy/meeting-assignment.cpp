#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>
#include <stack>
#include <deque>

//"https://www.acmicpc.net/problem/1931"

using namespace std;

int main()
{
	int n = 0;
	int result = 0;

	cin >> n;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	for (int i = 0; i < n; ++i)
	{
		int st = 0, en = 0;

		cin >> st >> en;

		pq.push({ en, st });
	}

	while (!pq.empty())
	{
		int cur_st, cur_en;

		tie(cur_en, cur_st) = pq.top(); pq.pop();

		result++;

		while (!pq.empty() && cur_en > pq.top().second) pq.pop();
	}

	cout << result;

	return 0;
}
