#include"../lib/mysort.h"
void solution()
{
    mysort test(8);
    test.print();
    test.radixsort();
    cout<<"radixsort:"<<endl;
    test.print();
}
int main()
{
    solution();
    return 0;
}