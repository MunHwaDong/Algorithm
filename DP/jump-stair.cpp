#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstring>
#include <iomanip>
#include <numeric>

using namespace std;

"https://www.acmicpc.net/problem/2579"

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void solve(int k)
{

}

int main()
{
    fastIO();

    //int t = 1; // 테스트 케이스가 여러 개인 경우 입력받아 사용
    //cin >> t; // 테스트 케이스 입력받는 경우 주석 해제


    // while(--t)
    // {
    //     cin >> n >> m;
    //     solve(0);
    // }


    int n = 0;

    cin >> n;

    vector<vector<int>> dp(n, vector<int>(2, 0));
    vector<int> score(n, 0);

    for(auto& ele : score)
        cin >> ele;
    
    if(n == 1)
    {
        cout << score[0];
        return 0;
    }
    
    dp[0][0] = score[0];
    dp[0][1] = 0; //불가능

    dp[1][0] = score[1]; //두번째 계단에 한 번만에 올라왔을 경우
    dp[1][1] = score[0] + score[1];

    for(int i = 2; i < n; ++i)
    {
        dp[i][0] = max(dp[i - 2][0], dp[i - 2][1]) + score[i];
        dp[i][1] = dp[i-1][0] + score[i];
    }

    cout << max(dp[n - 1][0], dp[n - 1][1]);
    
    return 0;
}
