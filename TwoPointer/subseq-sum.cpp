#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>
#include <deque>

//"https://www.acmicpc.net/problem/1806"

using namespace std;

int main()
{
	int n, m;

	cin >> n >> m;

	vector<int> s(n, 0);

	for (auto& ele : s)
	{
		cin >> ele;
	}

	int result = (int)1e9;

	int en = 1;
	int total = s[0];

	for (int st = 0; st < s.size(); ++st)
	{
		while (en < s.size() && total < m)
		{
			total += s[en++];
		}

		if(total >= m) result = min(result, en - st);

		total -= s[st];
	}

	result != (int)1e9 ? cout << result : cout << 0;

	return 0;
}
