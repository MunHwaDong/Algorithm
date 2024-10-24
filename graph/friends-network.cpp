#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <functional>

//"https://www.acmicpc.net/problem/4195"

using namespace std;

int FindParent(vector<int>& parents, int v)
{
    if(parents[v] == v) return v;
    else return parents[v] = FindParent(parents, parents[v]);
}

void Union(vector<int>& parents, int v1, int v2, vector<int>& net)
{
    v1 = FindParent(parents, v1);
    v2 = FindParent(parents, v2);

    if(v1 != v2)
    {
        parents[v2] = v1;
        net[v1] += net[v2];
    }
}

bool Find(vector<int>& parents, int v1, int v2)
{
    v1 = FindParent(parents, v1);
    v2 = FindParent(parents, v2);

    return v1 == v2;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL); cout.tie(NULL);

    int t;

    cin >> t;

    while(t--)
    {
        int f = 0;

        unordered_map<string, int> h;
        int id = 0;

        cin >> f;

        vector<int> set(f * 2);
        
        for(int i = 0; i < f * 2; ++i)
        {
            set[i] = i;
        }

        vector<int> net(f * 2, 1);

        for(int i = 0; i < f; ++i)
        {
            string p1, p2;

            cin >> p1 >> p2;

            if(h.find(p1) == h.end())
            {
                h.insert({p1, id++});
            }
            if(h.find(p2) == h.end())
            {
                h.insert({p2, id++});
            }

            Union(set, h[p1], h[p2], net);

            cout << net[FindParent(set, h[p1])] << '\n';
        }

        h.clear();
    }

    return 0;
}
