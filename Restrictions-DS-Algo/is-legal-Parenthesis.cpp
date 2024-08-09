#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstring>
#include <iomanip>
#include <numeric>

using namespace std;

"https://www.acmicpc.net/problem/4949"

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main()
{
    fastIO();

    while(1)
    {
        string str;

        getline(cin, str);
        if(str == ".") break;

        stack<char> s;
        bool a = true;

        for(auto ele : str)
        {
            if(ele == '(' || ele == '[')
            {
                s.push(ele);
            }
            else if(ele == ')' || ele == ']')
            {
                if(s.empty())
                {
                    a = false;
                    break;
                }

                if(s.top() == '(' && ele == ')'
                    || s.top() == '[' && ele == ']')
                {
                    s.pop();
                }
                else
                {
                    a = false;
                    break;
                }
            }
        }

        if(!s.empty()) a = false;
        
        if(a) cout << "yes" << '\n';
        else cout << "no" << '\n';
    }

    return 0;
}
