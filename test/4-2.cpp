#include "../lib/graph.h"

void solution()
{
    mygraph g(6,10,true);
    g.creategraph();
    g.print();
    g.getindegree();
    g.getoutdegree();
}

int main()
{
    solution();
    return 0;
}