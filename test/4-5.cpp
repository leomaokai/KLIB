#include"../lib/graph.h"
int main()
{
    listgraph test(6,10,true);
    test.createlistgraph();
    test.print();
    test.listdfs();
    return 0;
}