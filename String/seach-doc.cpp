#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>

"https://www.acmicpc.net/problem/1543"

using namespace std;

int main()
{

    string s1;
    string sep;

    getline(cin, s1);
    getline(cin, sep);

    int pos = s1.find(sep);
    int result = 0;

    while(pos != string::npos)
    {
        result++;

        pos = s1.find(sep, pos + sep.size());
    }

    cout << result << '\n';

    return 0;
}
