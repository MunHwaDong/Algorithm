#include <iostream>
#include <vector>

using namespace std;

int min(int a, int b)
{
	return a > b ? b : a;
}

int solved(int n)
{
	vector<int> dp(n + 1);

	dp[0] = 0;
	dp[1] = 0;
	
	if (n >= 2) dp[2] = 1;
	if (n >= 3) dp[3] = 1;

	for (int i = 4; i <= n; ++i)
	{
		dp[i] = dp[i - 1] + 1;

		if (i % 3 == 0)
		{
			dp[i] = min(dp[i], dp[i / 3] + 1);
		}
		if (i % 2 == 0)
		{
			dp[i] = min(dp[i], dp[i / 2] + 1);
		}
	}

	return dp[n];
}

int main()
{
	int num = 0;

    cin >> num;

    cout << solved(num) << endl;
    
    return 0;
}
