#include "lib/graph.h"
int main()
{
    mygraph test(8, 12, false);
    test.creategraph();
    test.print();
    cout << "dfs the graph" << endl;
    dfsam(test, 0);
    cout << endl;
    test.clear();
    cout << "bfs the graph" << endl;
    bfsam(test, 0);
    return 0;
}