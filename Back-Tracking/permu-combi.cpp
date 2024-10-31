#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>

//"https://www.acmicpc.net/problem/14889"

using namespace std;

int result = (int)1e9;

void solved(int idx, int n, vector<int>& t1, vector<int>& t2, vector<vector<int>>& s)
{
	if (idx == n)
	{
		//불필요한 연산 건너뛰기
		if (t1.size() != n / 2 || t2.size() != n / 2) return;

		int t1s = 0;
		int t2s = 0;

		for (int i = 0; i < n / 2; ++i)
		{
			for (int j = i; j < n / 2; ++j)
			{
				if (i != j)
				{
					t1s += s[t1[i]][t1[j]] + s[t1[j]][t1[i]];
					t2s += s[t2[i]][t2[j]] + s[t2[j]][t2[i]];
				}
			}
		}

		result = min(result, abs(t1s - t2s));
		return;
	}

	if (t1.size() < n / 2)
	{
		t1.push_back(idx);
		solved(idx + 1, n, t1, t2, s);
		t1.pop_back();
	}

	if (t2.size() < n / 2)
	{
		t2.push_back(idx);
		solved(idx + 1, n, t1, t2, s);
		t2.pop_back();
	}

	return;
}

int main()
{
	int n;

	cin >> n;

	vector<vector<int>> s(n, vector<int>(n, 0));

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> s[i][j];
		}
	}

	vector<int> t1, t2;

	solved(0, n, t1, t2, s);

	cout << result;

	return 0;
}
