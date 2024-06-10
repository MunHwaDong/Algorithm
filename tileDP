#include <iostream>
#include <vector>

int main()
{

    int n = 0;

    std::cin >> n;

    std::vector<int> dp(n + 1, 0);

    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 3;

    for(int i = 3; i <= n; ++i)
    {
        dp[i] = dp[i - 1] + 2 * dp[i - 2];
    }

    std::cout << dp[n] << std::endl;

    return 0;
}
