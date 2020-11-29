#include"../lib/graph.h"
void solution()
{
    mygraph test(6,10,false);
    test.creategraph();
    test.print();
    prim(test,0);
}
int main()
{
    solution();
    return 0;
}