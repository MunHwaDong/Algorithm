#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>

using namespace std;

vector<string> split(string& s, string sep)
{
    vector<string> result;

    int pos = 0;

    while(pos < s.size())
    {
        int nxt_pos = s.find(s, pos);

        if(nxt_pos == -1) nxt_pos = s.size();
        if(nxt_pos - pos > 0)
            result.push_back(s.substr(pos, nxt_pos - pos));

        pos = nxt_pos + sep.size();
    }

    return result;
}
