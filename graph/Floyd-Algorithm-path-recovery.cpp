#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <cmath>

"https://www.acmicpc.net/problem/11780"

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie();

    int n, m;

    cin >> n >> m;

    vector<vector<int>> g(n + 1, vector<int>(n + 1, int(1e9)));
    vector<vector<int>> next(n + 1, vector<int>(n + 1, int(1e9)));

    for(int i = 0; i < m; ++i)
    {
        int v1, v2, w;

        cin >> v1 >> v2 >> w;

       if(g[v1][v2] > w)
       {
            g[v1][v2] = w;
            next[v1][v2] = v2;
       }
    }

    for(int via = 1; via <= n; ++via)
    {
        for(int start = 1; start <= n; ++start)
        {
            for(int dest = 1; dest <= n; ++dest)
            {
                if(start == dest)
                {
                    g[start][dest] = 0;
                    next[start][dest] = 0;
                }
                else
                {
                    int viaPath = g[start][via] + g[via][dest];

                    if(g[start][dest] > viaPath)
                    {
                        g[start][dest] = viaPath;
                        next[start][dest] = next[start][via];
                    }
                }
            }
        }
    }

    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if(g[i][j] >= int(1e9))
                cout << "0 ";
            else
                cout << g[i][j] << " ";
        }
        cout << '\n';
    }

    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if(i == j || next[i][j] == int(1e9))
            {
                cout << "0\n";
            }
            else
            {
                vector<int> path;
                int start = i;

                while(start != j)
                {
                    path.push_back(start);
                    start = next[start][j];
                }
                path.push_back(j);

                cout << path.size() << " ";

                for(const auto& ele : path)
                {
                    cout << ele << " ";
                }
                cout << '\n';
            }
        }
    }
}
