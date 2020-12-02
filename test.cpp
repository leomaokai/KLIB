#include "lib/mysort.h"
int main()
{
    cout<<"input num:"<<endl;
    int n=0;
    cin>>n;
    mysort test(n);
    cout<<"quicksort:"<<endl;
    //test.insertsort();
    quicksort(test,0,n-1);
    //test.shellsort();
    //test.selectsort();
    return 0;
}