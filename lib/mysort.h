#ifndef MYSORT_H
#define MYSORT_H

#include "head.h"

class mysort
{
public:
    mysort(int n = 5) : _n(n),
                        arry(new int[_n]())
    {
        cout << "input val:" << endl;
        for (int i = 0; i < _n; ++i)
            cin >> arry[i];
    }
    ~mysort()
    {
        if (arry != nullptr)
            delete[] arry;
        arry = nullptr;
    }
    void bubblesort(); //冒泡排序
    void insertsort(); //插入排序
    void selectsort(); //选择排序
    void shellsort();  //希尔排序
    void radixsort();  //基数排序
    void print()
    {
        for (int i = 0; i < _n; ++i)
            cout << arry[i] << " ";
        cout << endl;
    }

private:
    int _n;
    int *arry;
    int maxbit();                                //基数排序求位数函数
    int bitnumber(const int &x, const int &bit); //基数排序求某位数函数

    friend void quicksort(mysort &test, int low, int high);      //快速排序
    friend int partition(mysort &test, int low, int high);       //快速排序分离函数
    friend void mergesort(mysort &test, int low, int high);      //归并排序
    friend void merge(mysort &test, int low, int mid, int high); //归并排序合并函数
};
//冒泡排序
void mysort::bubblesort()
{
    bool flag = true; //结束标志
    int i = 0;
    int j = 0;
    int temp = 0;
    while (flag)
    {
        flag = false;
        for (j = 0; j < _n - i - 1; ++j)
        {
            if (arry[j] > arry[j + 1]) //交换
            {
                temp = arry[j];
                arry[j] = arry[j + 1];
                arry[j + 1] = temp;
                flag = true; //发生交换则置为true
            }
        }
        ++i;
        print();
    }
}
//插入排序
void mysort::insertsort() //在已经有序的序列中找的合适的位置插入
{
    int i = 0;
    int j = 0;
    int temp = 0;
    for (i = 0; i < _n - 1; ++i)
    {
        if (arry[i] > arry[i + 1])
        {
            temp = arry[i + 1];    //临时保存第i+1个数
            arry[i + 1] = arry[i]; //将第i个数后移
            //在已经排好的序列中找位置
            for (j = i - 1; arry[j] > temp && j >= 0; --j) //从后往前找
                arry[j + 1] = arry[j];
            arry[j + 1] = temp;
        }
        print();
    }
}
//选择排序
void mysort::selectsort() //在待排序的序列中选择一个最小的元素与最前面的元素交换
{
    for (int i = 0; i < _n - 1; ++i)
    {
        int k = i;
        for (int j = i + 1; j < _n; ++j) //寻找待排序列中最小元素
            if (arry[j] < arry[k])
                k = j;
        if (k != i) //将最小元素与第i个交换
        {
            int temp = arry[i];
            arry[i] = arry[k];
            arry[k] = temp;
        }
        //print();
    }
}
//希尔排序
void mysort::shellsort()
{
    int gap = _n / 2; //以gap间隔两两对应比较交换
    int temp = 0;
    while (gap > 0)
    {
        for (int i = gap; i < _n; ++i)
        {
            temp = arry[i];         //从gap开始
            int preindex = i - gap; //与第i个数对应的数
            while (preindex >= 0 && arry[preindex] > temp)
            {
                arry[preindex + gap] = arry[preindex];
                preindex -= gap; //以gap为周期向前移动
            }
            arry[preindex + gap] = temp;
        }
        gap /= 2; //缩小间隔
        //print();
    }
}
//基数排序
int mysort::maxbit() //求序列中最大数的位数
{
    int maxvalue = arry[0];      //最大数
    int digits = 0;              //最大位数
    for (int i = 1; i < _n; ++i) //找最大数
        if (arry[i] > maxvalue)
            maxvalue = arry[i];
    while (maxvalue != 0)
    {
        ++digits;
        maxvalue /= 10;
    }
    return digits;
}
int mysort::bitnumber(const int &x, const int &bit) //求x第bit位上的数字
{
    int temp = 1;
    for (int i = 1; i < bit; ++i)
        temp *= 10;
    return (x / temp) % 10;
}
void mysort::radixsort() //应用到桶排序**画图理解**难
{
    int i, j, k, bit, max;
    max = maxbit();
    int **temparry = new int *[10]();
    for (i = 0; i < 10; ++i)
        temparry[i] = new int[_n + 1]();

    for (bit = 1; bit <= max; ++bit)
    {
        for (j = 0; j < _n; ++j)
        {
            int num = bitnumber(arry[j], bit);
            int index = ++temparry[num][0];
            temparry[num][index] = arry[j];
        }
        for (i = 0, j = 0; i < 10; ++i)
        {
            for (k = 1; k <= temparry[i][0]; ++k)
                arry[j++] = temparry[i][k];
            temparry[i][0] = 0;
        }
        print();
    }

    for (i = 0; i < 10; ++i)
        delete[] temparry[i];
    delete[] temparry;
}
//快速排序
void quicksort(mysort &test, int low, int high)
{
    int mid = 0;
    if (low < high)
    {
        mid = partition(test, low, high);
        quicksort(test, low, mid - 1);  //递归基准位置前的序列
        quicksort(test, mid + 1, high); //递归基准位置后的序列
        //test.print();
    }
}
int partition(mysort &test, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = test.arry[i]; //以第一个数为基准
    while (i < j)
    {
        while (i < j && test.arry[j] > pivot) //从右向左移动指针直到遇到比基准小的数
            j--;
        while (i < j && test.arry[i] <= pivot) //从左向右移动指针直到遇到比基准大的数
            i++;
        if (i < j)
            swap(test.arry[i++], test.arry[j--]); //交换这两个数并移动指针
    }
    //移动准基位置,此后基准数确定了在序列中的位置,返回基准数的位置
    if (test.arry[i] > pivot)
    {
        swap(test.arry[i - 1], test.arry[low]);
        return i - 1;
    }
    swap(test.arry[i], test.arry[low]);
    return i;
}
//归并排序
void mergesort(mysort &test, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;     //以中心分成两个序列
        mergesort(test, low, mid);      //递归前序列
        mergesort(test, mid + 1, high); //递归后序列
        merge(test, low, mid, high);    //合并
        //test.print();
    }
}
void merge(mysort &test, int low, int mid, int high)
{
    int *temparry = new int[high - low + 1]();
    int i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high) //序列的两部分合并
    {
        if (test.arry[i] <= test.arry[j])
            temparry[k++] = test.arry[i++];
        else
            temparry[k++] = test.arry[j++];
    }
    //多余序列移动
    while (i <= mid)
        temparry[k++] = test.arry[i++];
    while (j <= high)
        temparry[k++] = test.arry[j++];
    //将序列移到原空间
    for (i = low, k = 0; i <= high; ++i)
        test.arry[i] = temparry[k++];
    delete[] temparry;
}
#endif