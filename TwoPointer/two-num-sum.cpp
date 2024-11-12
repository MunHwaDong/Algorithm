#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

//"https://www.acmicpc.net/problem/3273"

using namespace std;

int main()
{

    int n, m;

    cin >> n;

    vector<int> seq(n);

    for(auto& ele : seq)
    {
        cin >> ele;
    }

    cin >> m;

    sort(seq.begin(), seq.end());

    int left = 0, right = n - 1;
    int result = 0;

    while(left < right)
    {
        int sum = seq[left] + seq[right];

        if(sum == m)
        {
            result++;
            left++;
        }

        else if(sum > m) right--;
        else if(sum < m) left++;
    }

    cout << result;

    return 0;
}
