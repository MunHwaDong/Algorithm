#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>
#include <stack>
#include <deque>

//"https://www.acmicpc.net/problem/9012"

using namespace std;

int main()
{
	int t = 0;

	cin >> t;

	while (t--)
	{
		string str;

		stack<char> s;
		bool isVPS = true;

		cin >> str;

		for (const auto& c : str)
		{
			if (c == '(')
			{
				s.push(c);
			}
			else if (c == ')')
			{
				if (s.empty())
				{
					isVPS = false;
					break;
				}
				else
				{
					s.pop();
				}
			}
		}

		if (s.empty() && isVPS) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}
