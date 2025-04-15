#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <map>
#include <stack>

//최적화 x 버전, 최적화해야 모든 테스트 케이스가 통과된다.
//https://school.programmers.co.kr/learn/courses/30/lessons/389480

using namespace std;

int minVal = 1e9;

void solved(vector<vector<int>>& items, int thiefA, int thiefB, int itemIdx, int n, int m)
{
    if(thiefA >= n || thiefB >= m)
        return;
    
    if(itemIdx == items.size())
    {
        if(thiefA < n && thiefB < m)
        {
            minVal = min(minVal, thiefA);
        }
        
        return;
    }

    solved(items, thiefA + items[itemIdx][0], thiefB, itemIdx + 1, n, m);

    solved(items, thiefA, thiefB + items[itemIdx][1], itemIdx + 1, n, m);
}

int solution(vector<vector<int>> info, int n, int m)
{
    minVal = 1e9;
    int answer = 0;

    solved(info, 0, 0, 0, n, m);

    answer = (minVal == 1e9) ? -1 : minVal;

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
