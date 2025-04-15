#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <map>
#include <stack>

//https://school.programmers.co.kr/learn/courses/30/lessons/389480

using namespace std;

const int INF = 1e9;

int solved(vector<vector<vector<int>>>& dp, vector<vector<int>>& items, int thiefA, int thiefB, int itemIdx, int n, int m)
{
    if(thiefA >= n || thiefB >= m)
        return INF;
    
    if(itemIdx == items.size())
    {
        if(thiefA < n && thiefB < m)
        {
            return thiefA;
        }
        else
            return INF;
    }

    if(dp[itemIdx][thiefA][thiefB] != -1)
        return dp[itemIdx][thiefA][thiefB];

    int ta = solved(dp, items, thiefA + items[itemIdx][0], thiefB, itemIdx + 1, n, m);

    int tb = solved(dp, items, thiefA, thiefB + items[itemIdx][1], itemIdx + 1, n, m);

    return dp[itemIdx][thiefA][thiefB] = min(ta, tb);
}

int solution(vector<vector<int>> info, int n, int m)
{
    int answer = 0;
    vector<vector<vector<int>>> dp(101, vector<vector<int>>(301, vector<int>(301, -1)));

    answer = solved(dp, info, 0, 0, 0, n, m);

    answer = (answer == INF) ? -1 : answer;

    return answer;
}

int main()
{
    vector<vector<int>> info1 {{{1, 2}, {2, 3}, {2, 1}}};
    vector<vector<int>> info2 {{{1, 2}, {2, 3}, {2, 1}}};
    vector<vector<int>> info3 {{{3, 3}, {3, 3}}};

    cout << solution(info1, 4, 4) << endl;
    cout << solution(info2, 1, 7) << endl;
    cout << solution(info3, 6, 1) << endl;

    return 0;
}
