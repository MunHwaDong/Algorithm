#include <iostream>

int MCSS(int seq[], int n);

int main()
{

    int n{0};

    std::cin >> n;

    int seq[n];

    for(int i = 0; i < n; ++i)
        std::cin >> seq[i];

    std::cout << MCSS(seq, n) << std::endl;

    return 0;
    
}

int MCSS(int seq[], int n)
{

    int dp[n] {0};
    int negative {-1};
    bool flag {false};
    
    dp[0] = seq[0];

    int max {dp[0]};

    for(int i = 1, j = 0; i < n; ++i, ++j)
    {
        dp[i] = dp[j] + seq[i];

        if(dp[i] < 0)
            dp[i] = 0;

        if(dp[i] > max)
            max = dp[i];
        
    }

    for(int i = 0; i < n; ++i)
    {

        if(seq[i] >= 0)
            flag = true;

        if(negative < seq[i])
            negative = seq[i];

    }

    if(flag == true)
        return max;
    else
        return negative;

}
