#include "lib/seqlist.h"
#include "lib/sinlist.h"
int main()
{
    sinlist<int> test;
    for(int i=0;i<10;++i)
    {
        test.push_back(rand()%100+1);
    }
    test.print();
    int temp=test.getval(9);
    cout<<temp<<endl;
    cout<<test.findval(70)<<endl;
    test.insert(4,80);
    test.print();
    return 0;
}