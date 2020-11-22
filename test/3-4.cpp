#include"../lib/binarytree.h"
//RAD``B`C``EF``GH`I```
void solution()
{
    binarytree<char> test;
    test.createtree();
    cout<<"nodes: "<<test.sizetree()<<endl;
    cout<<"depth: "<<test.depth()<<endl;
    cout<<"leaves:"<<test.sizeleft()<<endl;
}
int main()
{
    solution();
    return 0;
}