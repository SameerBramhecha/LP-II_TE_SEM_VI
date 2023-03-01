// Selection Sort#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

vector<int> selectionsort(vector<int> a)
{
    int n = a.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min_indx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[min_indx])
            {
                min_indx = j;
            }
        }
        swap(a[i], a[min_indx]);
    }
    return a;
}

int main()
{
    vector<int> a = {8, 5, 7, 6, 2, 3, 4};
    int n = a.size();
    cout << "Unsorted Array: " << endl;
    for (auto i : a)
    {
        cout << i << " ";
    }
    cout << endl;
    a = selectionsort(a);
    cout << "Sorted Array: " << endl;
    for (auto i : a)
    {
        cout << i << " ";
    }
    cout << endl;
}