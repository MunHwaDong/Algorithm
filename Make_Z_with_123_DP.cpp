#include <iostream>
#include <vector>

int main()
{
    int loop = 0;

    std::cin >> loop;

    while(loop-- > 0)
    {
        int n = 0;

        std::cin >> n;

        std::vector<int> dp(n + 1);

        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 4;

        for(int i = 4; i <= n; ++i)
        {
            dp[i] = dp[i - 3] + dp[i - 2] + dp[i - 1];
        }

        std::cout << dp[n] << std::endl;
    }

    return 0;
}
