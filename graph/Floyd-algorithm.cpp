#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

"https://www.acmicpc.net/problem/11404"

using namespace std;

int main()
{
    int n, m;

    cin >> n >> m;

    vector<vector<int>> g(n + 1, vector<int>(n + 1, int(1e9)));

    for(int i = 0; i < m; ++i)
    {
        int v1, v2, w;

        cin >> v1 >> v2 >> w;

        g[v1][v2] = min(g[v1][v2], w);
    }

    for(int via = 1; via <= n; ++via)
    {
        for(int start = 1; start <= n; ++start)
        {
            for(int dest = 1; dest <= n; ++dest)
            {
                if(start == dest) g[start][dest] = 0;
                else 
                    g[start][dest] = min(g[start][dest], g[start][via] + g[via][dest]);
            }
        }
    }

    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if(g[i][j] >= int(1e9)) cout << "0 ";
            else cout << g[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
