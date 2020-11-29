#include"../lib/graph.h"

void solution()
{
    mygraph test(6,10,true);
    test.creategraph();
    test.print();
    floyd(test);
}
int main()
{
    solution();
    return 0;
}