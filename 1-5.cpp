#include "lib/head.h"
clock_t start, finish;
void test1(const int &n)
{
    start = clock();
    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum++;
    finish = clock();
    cout << "test1 n="<<n<<" t:" << finish - start << endl;
}
void test2(const int &n)
{
    start = clock();
    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum += i;
    finish = clock();
    cout << "test1 n="<<n<<" t:" << finish - start << endl;
}
void test3(const int &n)
{
    start = clock();
    int sum = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            sum++;
    finish = clock();
    cout << "test1 n="<<n<<" t:" << finish - start << endl;
}
int main()
{
    test1(1000);
    test1(10000);
    test1(100000);
    test2(1000);
    test2(10000);
    test2(100000);
    test3(1000);
    test3(10000);
    test3(100000);
    return 0;
}