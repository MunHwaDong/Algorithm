#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>
#include <deque>

//"https://www.acmicpc.net/problem/2470"

using namespace std;

int main()
{
	int n;

	cin >> n;

	vector<long long> s(n, 0);

	for (auto& ele : s)
	{
		cin >> ele;
	}

	sort(s.begin(), s.end());

	int left = 0;
	int right = n - 1;
	long long result = (long long)1e10;

	int lidx = 0;
	int ridx = n - 1;

	while (left < right)
	{
		long long sum = s[left] + s[right];

		if (abs(sum) < result)
		{
			result = abs(sum);
			lidx = left;
			ridx = right;
		}

		if (sum > 0) right--;
		else left++;

	}

	cout << s[lidx] << " " << s[ridx];

	return 0;
}
