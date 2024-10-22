#include <iostream>
#include <vector> // 가변 길이 배열
#include <list> //링크드 리스트 (Doubly Linked List)
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue> //우선순위큐 포함
#include <stack>
#include <deque>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstring>
#include <iomanip>
#include <numeric>

//"https://www.acmicpc.net/problem/1655"

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, num;

	cin >> n;

	priority_queue<int, vector<int>, greater<int>> minq;

	priority_queue<int> maxq;

	for (int i = 0; i < n; ++i)
	{
		cin >> num;

		if (i == 0)
		{
			maxq.push(num);
		}
		else if (i == 1)
		{
			if (num > maxq.top())
			{
				minq.push(num);
			}
			else
			{
				minq.push(maxq.top());
				maxq.pop();
				maxq.push(num);
			}
		}
		else
		{
			maxq.push(num);

			if (maxq.top() > minq.top())
			{
				maxq.pop();
				minq.push(num);

				if (minq.size() > maxq.size())
				{
					maxq.push(minq.top());
					minq.pop();
				}
			}

			if (maxq.size() - minq.size() > 1)
			{
				minq.push(maxq.top());
				maxq.pop();
			}
		}

		cout << maxq.top() << '\n';
	}
	
	return 0;
}
