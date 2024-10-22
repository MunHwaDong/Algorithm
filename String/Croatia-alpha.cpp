#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>

"https://www.acmicpc.net/problem/2941"

using namespace std;

int main()
{

    ios::sync_with_stdio(0);
    cin.tie();

    vector<string> croa = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z="};

    string str;

    cin >> str;

    int result = 0;

    for(const auto& alpha : croa)
    {
        while(true)
        {
            int pos = str.find(alpha);

            if(pos == string::npos) break;

            str.replace(pos, alpha.size(), "#");
        }
    }

    cout << str.size() << endl;

    return 0;
}
