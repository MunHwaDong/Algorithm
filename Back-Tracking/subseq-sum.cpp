#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <utility>

//"https://www.acmicpc.net/problem/1182"

using namespace std;

int result = 0;

void solved(int k, vector<int>& seq, int idx, int s)
{
    if (idx >= seq.size())
    {
        if (k == s)
        {
            result++;
        }
        return;
    }

    solved(k, seq, idx + 1, s);
    solved(k + seq[idx], seq, idx + 1, s);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL); cout.tie(NULL);

    int n = 0;
    int s = 0;
    
    cin >> n >> s;

    vector<int> seq(n, 0);

    for (auto& ele : seq)
    {
        cin >> ele;
    }

    if (s == 0) result--;

    solved(0, seq, 0, s);

    cout << result;

    return 0;
}
