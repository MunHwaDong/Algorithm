#include <iostream>
#include <vector>

int main()
{
    int n = 0;

    std::cin >> n;

    std::vector<int> dp(n + 1, 0);

    dp[0] = 1;
    dp[1] = 3;

    for(int i = 2; i <= n; ++i)
    {
        dp[i] = (2 * dp[i-1] + dp[i-2]) % 9901;
    }

    std::cout << dp[n] % 9901 << std::endl;

    return 0;
}
