#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstring>
#include <iomanip>
#include <numeric>

/*
https://www.acmicpc.net/problem/10808
*/

using namespace std;

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

vector<int> solve(string in)
{
    vector<int> al(26);

    for(int idx = 0; idx < in.length(); ++idx)
    {
        al[tolower(in[idx]) - 'a']++;
    }

    return al;
}

int main()
{
    fastIO();

    int t = 1; // 테스트 케이스가 여러 개인 경우 입력받아 사용
    // cin >> t; // 테스트 케이스 입력받는 경우 주석 해제

    string in;

    while (t--)
    {
        cin >> in;

        vector<int> sol(solve(in));

        for(const auto& ele : sol)
        {
            cout << ele << " ";
        }
    }
    return 0;
}
