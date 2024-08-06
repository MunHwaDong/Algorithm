#include <iostream>

void merge(int* arr, int start, int mid, int end)
{
    int* tmparr = new int[2 * (start + end)];
    int idx = 0;
    int spointer = start;
    int mpointer = mid + 1;

    while(spointer <= mid && mpointer <= end)
    {
        if(arr[spointer] > arr[mpointer])
        {
            tmparr[idx] = arr[mpointer];
            ++mpointer;
            ++idx;
        }
        else
        {
            tmparr[idx] = arr[spointer];
            ++spointer;
            ++idx;
        }
    }
    
    while(spointer <= mid) tmparr[idx++] = arr[spointer++];
    while(mpointer <= end) tmparr[idx++] = arr[mpointer++];

    idx = 0;

    for(int i = start; i <= end; ++i)
    {
        arr[i] = tmparr[idx++];
    }
    
    delete[] tmparr;
}

void solved(int* arr, int start, int end)
{
    int mid = 0;

    if(start < end)
    {
        mid =  (start + end)/2;

        solved(arr, start, mid);
        solved(arr, mid + 1, end);
    }
    else
    {
        return;
    }

    merge(arr, start, mid, end);
}

/*

    in : start, end, arr
    out : arr

        1. 배열의 각 지점의 인덱스를 나타내는 start, end가 start + 1 == end일 때까지 재귀적으로 end/2, start = end/2 + 1로 호출한다.
        2. 분할이 끝나면, 해당 배열을 리턴한다.
        3. 자식들에게 리턴 받은 두 배열을 2포인터로 비교하며 머지한다.
*/

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int length = 0;

    std::cin >> length;

    int* arr = new int[length];

    for(int i = 0; i < length; ++i)
        std::cin >> arr[i];

    solved(arr, 0, length - 1);

    for(int i = 0; i < length; ++i)
        std::cout << arr[i] << "\n";

    delete[] arr;

    return 0;
}
