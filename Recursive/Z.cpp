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

"https://www.acmicpc.net/problem/1074"

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int solve(int n, int r, int c)
{
    if(n <= 0) return 0;

    //2의 제곱
    int half = 1 << (n-1);

    if(r < half && c < half) return solve(n-1, r, c);
    if(r < half && c >= half) return half*half + solve(n-1, r, c-half);
    if(r >= half && c < half) return 2*half*half + solve(n-1, r-half, c);
    
    return 3*half*half + solve(n-1, r-half, c-half);
}

int main()
{
    fastIO();

    int t = 1; // 테스트 케이스가 여러 개인 경우 입력받아 사용
    // cin >> t; // 테스트 케이스 입력받는 경우 주석 해제

    // while(--t)
    // {

    int n = 0, r = 0, c = 0;

    cin >> n >> r >> c;

    cout << solve(n, r, c);

    return 0;
}
