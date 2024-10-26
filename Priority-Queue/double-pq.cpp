#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <utility>

//"https://www.acmicpc.net/problem/7662"

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL); cout.tie(NULL);

    int t;

    cin >> t;

    while (t--)
    {
        int n = 0;

        cin >> n;

        priority_queue<long long> maxq;
        priority_queue<long long, vector<long long>, greater<long long>> minq;

        unordered_map<long long, long long> table;

        for (int i = 0; i < n; ++i)
        {
            char comm = 0;
            long long num = 0;

            cin >> comm >> num;

            if (comm == 'I')
            {
                if (table.find(num) == table.end())
                {
                    table.insert({ num, 1 });
                }
                else
                {
                    table[num] += 1;
                }

                maxq.push(num);
                minq.push(num);

            }
            else if (comm == 'D')
            {
                if (num == -1)
                {
                    while (!minq.empty() && table[minq.top()] == 0)
                    {
                        minq.pop();
                    }

                    if (!minq.empty())
                    {
                        table[minq.top()] -= 1;
                        minq.pop();
                    }
                }
                else if (num == 1)
                {
                    while (!maxq.empty() && table[maxq.top()] == 0)
                    {
                        maxq.pop();
                    }

                    if (!maxq.empty())
                    {
                        table[maxq.top()] -= 1;
                        maxq.pop();
                    }
                }
            }
        }
        bool is_empty = true;

        for (const auto& ele : table)
        {
            if (ele.second > 0) is_empty = false;
        }

        if (!is_empty)
        {
            while (!maxq.empty() && table[maxq.top()] <= 0) maxq.pop();
            while (!minq.empty() && table[minq.top()] <= 0) minq.pop();

            cout << maxq.top() << " " << minq.top() << '\n';
        }
        else
        {
            cout << "EMPTY" << '\n';
        }
    }

    return 0;
}
