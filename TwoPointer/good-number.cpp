#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>
#include <deque>

//"https://www.acmicpc.net/problem/1253"

using namespace std;

int main()
{
	int n;

	cin >> n;

	vector<int> seq(n, 0);

	for (int i = 0; i < n; ++i)
		cin >> seq[i];

	sort(seq.begin(), seq.end());

	int result = 0;

	for (int idx = 0; idx < n; ++idx)
	{
		int left = 0, right = n - 1;

		while (left < right)
		{
			if (left == idx)
			{
				left++;
				continue;
			}
			if (right == idx)
			{
				right--;
				continue;
			}

			int sum = seq[left] + seq[right];

			if (sum > seq[idx]) right--;
			else if (sum < seq[idx]) left++;

			else if (sum == seq[idx])
			{
				result++;
				break;
			}
		}
	}

	cout << result;

	return 0;
}
