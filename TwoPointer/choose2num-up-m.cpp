#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

//"https://www.acmicpc.net/problem/2230"

int main()
{
    int n, m;

    cin >> n >> m;

    vector<long long> seq(n, 0);

    for(auto& ele : seq)
    {
        cin >> ele;
    }

    sort(seq.begin(), seq.end());

    int right = 0;
    long long result = (long long)1e10;

    for(int left = 0; left < n; left++)
    {
        while(right < n && seq[right] - seq[left] < m) right++;
        if(right >= n) break;

        result = min(result, seq[right] - seq[left]);
    }

    cout << result;

    return 0;
}
