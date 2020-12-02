#include <iostream>
using namespace std;
const int n = 8;
int partition(int r[], int low, int high)
{
    int i = low, j = high, pivot = r[low];
    while (i < j)
    {
        while (i < j && r[j] > pivot) //从右向左扫描
            j--;
        if (i < j)
            swap(r[i++], r[j]);
        while (i < j && r[i] <= pivot) //从左向右扫描
            i++;
        if (i < j)
            swap(r[i], r[j--]);
    }
    for (int i = 0; i < n; ++i)
    {
        cout << r[i] << " ";
    }
    cout << endl;
    return i;
}
void quicksort(int r[], int low, int high)
{
    int mid = 0;
    if (low < high)
    {
        mid = partition(r, low, high); //基准位置
        quicksort(r, low, mid - 1);    //左序列递归快排
        quicksort(r, mid + 1, high);   //右序列递归快排
    }
}
int main()
{
    int r1[n] = {10, 80, 45, 3, 65, 23, 98, 8};
    quicksort(r1, 0, n - 1);
    cout << endl;
    int r2[n] = {3, 8, 10, 23, 45, 65, 80, 98};
    quicksort(r2, 0, n - 1);
    cout << endl;
    int r3[n] = {98, 80, 65, 45, 23, 10, 8, 3};
    quicksort(r3, 0, n - 1);
    return 0;
}