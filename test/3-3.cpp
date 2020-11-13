#include"../lib/binarytree.h"
int main()
{
    binarytree<char> test1(5);
    test1.createhuffmantree();
    test1.preorder();
    test1.inorder();
    test1.postorder();
    return 0;
}