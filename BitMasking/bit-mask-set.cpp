#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>
#include <stack>
#include <deque>

"https://www.acmicpc.net/problem/11723"

using namespace std;

class BitSet
{
public:
	void Add(int x)
	{
		x -= 1;

		set |= (1 << x);
	}

	void Remove(int x)
	{
		x -= 1;

		set &= (~(1 << x));
	}

	void Check(int x)
	{
		x -= 1;

		if (set & (1 << x))
		{
			cout << 1 << '\n';
		}
		else
			cout << 0 << '\n';
	}

	void Toggle(int x)
	{
		x -= 1;

		set ^= (1 << x);
	}

	void All()
	{
		set = (1 << 20) - 1;
	}

	void Empty()
	{
		set = 0;
	}

private:
	//0 <= x <= 20 / 0000 0000 0000 | 0000 0000 0000 0000 0000
	unsigned int set = 0;
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	BitSet set;

	int t = 0;

	cin >> t;

	while (t--)
	{
		string command;

		int x = 0;

		cin >> command;

		if (command == "add")
		{
			cin >> x;

			set.Add(x);
		}
		else if (command == "remove")
		{
			cin >> x;

			set.Remove(x);
		}
		else if (command == "check")
		{
			cin >> x;

			set.Check(x);
		}
		else if (command == "toggle")
		{
			cin >> x;

			set.Toggle(x);
		}
		else if (command == "all")
		{
			set.All();
		}
		else if (command == "empty")
		{
			set.Empty();
		}
	}

	return 0;
}
