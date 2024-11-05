#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

#define r first
#define c second

using namespace std;

//"https://www.acmicpc.net/problem/15686"

vector<pair<int, int>> h;
vector<pair<int, int>> c;

int result = (int)1e9;

void solved(vector<pair<int, int>>& choose)
{
    int tmpResult = 0;

    for(int house = 0; house < h.size(); ++house)
    {
        int tmpMin = (int)1e9;

        for(int chicken = 0; chicken < choose.size(); ++chicken)
        {
            int chickenDis = abs(h[house].r - choose[chicken].r) + abs(h[house].c - choose[chicken].c);

            if(tmpMin > chickenDis)
            {
                tmpMin = chickenDis;
            }
        }

        tmpResult += tmpMin;

        //조기 종료
        if(tmpResult >= result) return;
    }
        
    if(result > tmpResult) result = tmpResult;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL); cout.tie(NULL);

    int n, m;

    cin >> n >> m;

    vector<vector<int>> map(n, vector<int>(n, 0));
    vector<bool> vis(n, false);
    vector<pair<int, int>> choose;

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            cin >> map[i][j];

            if(map[i][j] == 1) h.push_back({i + 1, j + 1});
            else if(map[i][j] == 2) c.push_back({i + 1, j + 1});
        }
    }

    vector<int> comb(c.size(), 0);

    fill(comb.end() - m, comb.end(), 1);

    do
    {
        vector<pair<int, int>> choose;

        for(int i = 0; i < c.size(); ++i)
        {
            if(comb[i] == 1) 
            {
                choose.push_back(c[i]);
            }
        }

        solved(choose);

    } while (next_permutation(comb.begin(), comb.end()));
    

    cout << result;

    return 0;
}
