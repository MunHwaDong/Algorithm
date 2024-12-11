using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class QuickSort<T> where T : IComparable<T>
{
    private static void Quick_Sort(ref List<T> arr, int st, int en)
    {
        if (st + 1 >= en) return;
        else
        {
            T pivot = arr[st];
            int left = st + 1;
            int right = en;

            while (true)
            {
                while (left <= right && arr[left].CompareTo(pivot) <= 0) left++;
                while (left <= right && arr[right].CompareTo(pivot) >= 0) right--;

                if (left > right) break;
                
                (arr[left], arr[right]) = (arr[right], arr[left]);
            }

            (arr[st], arr[right]) = (arr[right], arr[st]);
            
            Quick_Sort(ref arr, st, right);
            Quick_Sort(ref arr, right + 1, en);
        }
    }
    
}
