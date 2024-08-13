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
"https://www.acmicpc.net/problem/9663"

vector<bool> colcheck(14, 0);
vector<bool> nwcheck(14, 0);
vector<bool> swcheck(14, 0);

int counts = 0;
int n = 0;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void solve(int k)
{
    if(k == n)
    {
        ++counts;
        return;
    }

    for(int idx = 0; idx < n; ++idx)
    {
        if(colcheck[idx] || nwcheck[k+idx] || swcheck[idx-k+n-1]) continue;

        colcheck[idx] = 1;
        nwcheck[k+idx] = 1;
        swcheck[idx-k+n-1] = 1;

        solve(k+1);

        colcheck[idx] = 0;
        nwcheck[k+idx] = 0;
        swcheck[idx-k+n-1] = 0;
    }
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
    
    cin >> n;

    solve(0);

    cout << counts;

    return 0;
}
