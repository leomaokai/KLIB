#include"../lib/binarytree.h"
//RAD``B`C``EF``GH`I```
void solution()
{
    binarytree<char> test;
    test.createtree();
    cout<<"leaves: "<<test.sizetree()<<endl;
    cout<<"depth: "<<test.depth()<<endl;
}
int main()
{
    solution();
    return 0;
}