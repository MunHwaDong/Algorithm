#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int FindParent(vector<int>& parents, int idx)
{
    if(parents[idx] == idx) return idx;
    else
    {
        return FindParent(parents, parents[idx]);
    }
}

void Union(vector<int>& parents, int v1, int v2)
{
    int v1Parents = FindParent(parents, v1);
    int v2Parents = FindParent(parents, v2);

    if(v1Parents < v2Parents) parents[v2Parents] = v1Parents;
    else parents[v1Parents] = v2Parents;
}

bool Find(vector<int>& parents, int v1, int v2)
{
    int v1Parents = FindParent(parents, v1);
    int v2Parents = FindParent(parents, v2);

    return v1Parents == v2Parents;
}
