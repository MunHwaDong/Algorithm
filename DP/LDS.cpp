#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>
#include <deque>

//"https://www.acmicpc.net/problem/18353"

using namespace std;

int main()
{

	int n = 0;

	cin >> n;

	vector<int> seq(n);

	for (int i = 0; i < n; ++i)
		cin >> seq[i];

	vector<int> dp(n, 1);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (seq[i] < seq[j])
			{
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}

	cout << n - *max_element(dp.begin(), dp.end());

	return 0;
}
