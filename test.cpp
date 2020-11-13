#include"lib/binarytree.h"
int main()
{
    //binarytree<int> test1;
    //test1.createtree();
    //cout<<test1.sizeleft()<<endl;
    //cout<<test1.depth()<<endl;
    //test1.preorder();
    //test1.inorder();
    //test1.postorder();
    //test1.createtree();
    //test1.preorder();
    binarytree<char> test2(5);
    test2.createhuffmantree();
    cout<<test2.sizeleft()<<endl;
    cout<<test2.depth()<<endl;
    //binarytree<char> test3;
    //test3.createtree();
    //cout<<test3.sizeleft()<<endl;
    //cout<<test3.depth()<<endl;
    return 0;
}