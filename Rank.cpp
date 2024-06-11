#include <iostream>
#include <vector>
#include <algorithm>

int solved(std::vector<int>& rankingScores, int score, int p, int n)
{
    int rank = 1;
    int duplicated = 0;
    //입력 받는 랭킹들은, 내림차순이 아니니깐 정렬하고 내림차순으로 만든다.
    sort(rankingScores.begin(), rankingScores.end(), std::greater<int>());
    rankingScores.resize(n);

    for(int i = 1; i < rankingScores.size(); ++i)
    {
            if(rankingScores[0] < score)
                return 1;

            while(rankingScores[i - 1] == rankingScores[i] && i < n)
            {
                ++duplicated;
                ++i;
            }

            if(rankingScores[i - 1] <= score)
            {
                return (rank + duplicated < p) ? rank : -1;
            }

            rank += duplicated;
            duplicated = 0;

            if(rank > p) return -1;
            else if(i < n) ++rank;
    }
        //end()는 끝 보다 항상 하나 더 뒤를 포인트 하고 있다는 것을 잊지 말자...
        rank = (*(--rankingScores.end()) > score) ? rank + 1 : rank;
        duplicated = (*(--rankingScores.end()) == score) ? duplicated + 1 : duplicated;

        return ((rank + duplicated) <= p) ? rank : -1;
}

int main()
{
    /*
        In
            n : 입력받을 점수 리스트의 길이(int)
            score : 태수의 점수(int)
            p : 랭킹에 등록 될 수 있는 리스트의 길이(int)
            Ranking Scores : 정렬되어 있지 않는 점수들의 리스트(arr or vector)
        
        Out
            solved : 입력받은 Ranking Scores에서 score의 순위.

        note
            동점일 경우, 공동 순위를 가진다.
            동점들 다음 나오는 순위는, 공동 순위들의 개수 만큼 더한 순위가 된다.
            랭킹안에 들 수 없을 경우, -1을 return 한다.
            모든 점수는 signed int보다 작은 값들이 들어온다.
    */

    int n, score, p = 0;

    std::cin >> n >> score >> p;

    std::vector<int> rankingScores(n);

    for(int i = 0; i < n; ++i)
    {
        std::cin >> rankingScores[i];
    }

    if (n == 0 && p == 0)
        std::cout << -1 << std::endl;
    else if(n == 0)
        std::cout << 1 << std::endl;
    else
        std::cout << solved(rankingScores, score, p, n) << std::endl;

    return 0;
}
