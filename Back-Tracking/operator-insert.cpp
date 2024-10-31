#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>

//"https://www.acmicpc.net/problem/14888"

using namespace std;

int oper[4];
int rmax = -(int)1e9;
int rmin = (int)1e9;

void solved(int idx, int n, vector<int>& o, vector<int>& seq)
{
	if (idx == n - 1)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (oper[i] != 0) return;
		}
		
		int calc = 0;

		if (o[0] == 0) calc = seq[0] + seq[1];
		else if (o[0] == 1) calc = seq[0] - seq[1];
		else if (o[0] == 2) calc = seq[0] * seq[1];
		else if (o[0] == 3) calc = seq[0] / seq[1];

		for (int i = 2; i < n; ++i)
		{
			switch (o[i - 1])
			{
			case 0:
				calc += seq[i];
				break;
			case 1:
				calc -= seq[i];
				break;
			case 2:
				calc *= seq[i];
				break;
			case 3:
				calc /= seq[i];
				break;
			default:
				break;
			}
		}

		rmax = max(rmax, calc);
		rmin = min(rmin, calc);

		return;
	}

	if (oper[0] > 0)
	{
		oper[0]--;
		o.push_back(0);
		solved(idx + 1, n, o, seq);
		o.pop_back();
		oper[0]++;
	}

	if (oper[1] > 0)
	{
		oper[1]--;
		o.push_back(1);
		solved(idx + 1, n, o, seq);
		o.pop_back();
		oper[1]++;
	}

	if (oper[2] > 0)
	{
		oper[2]--;
		o.push_back(2);
		solved(idx + 1, n, o, seq);
		o.pop_back();
		oper[2]++;
	}

	if (oper[3] > 0)
	{
		oper[3]--;
		o.push_back(3);
		solved(idx + 1, n, o, seq);
		o.pop_back();
		oper[3]++;
	}

	return;
}

int main()
{
	int n = 0;

	cin >> n;

	vector<int> seq(n, 0);

	for (auto& ele : seq)
	{
		cin >> ele;
	}

	for (auto& ele : oper)
	{
		cin >> ele;
	}

	vector<int> o;

	solved(0, n, o, seq);

	cout << rmax << " " << rmin;

	return 0;
}
