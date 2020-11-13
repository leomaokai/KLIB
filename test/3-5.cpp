#include"../lib/head.h"
typedef struct Bnode //二叉树存储结构
{
    char data;
    struct Bnode *lchild;
    struct Bnode *rchild;
} Bnode, *Btree;
Btree pre_in_creatrtree(const char *pre, const char *mid, int len) //先序中序还原树
{
    if (len == 0)
        return nullptr;
    char ch = pre[0];
    int index = 0;
    while (mid[index] != ch)
        index++;
    Btree T = new Bnode();
    T->data = ch;
    T->lchild = pre_in_creatrtree(pre + 1, mid, index);
    T->rchild = pre_in_creatrtree(pre + index + 1, mid + index + 1, len - index - 1);
    return T;
}
void preorder2(Btree T)
{
    if(T!=nullptr)
    {
        cout<<T->data;
        preorder2(T->lchild);
        preorder2(T->rchild);
    }
}
void preorder1(Btree T)
{
    if(T!=nullptr)
    {
        cout<<"data: "<<T->data<<endl;
        cout<<"lchild: ";
        preorder2(T->lchild);
        cout<<endl;
        cout<<"rchild: ";
        preorder2(T->rchild);
        cout<<endl;
        cout<<endl;

        preorder1(T->lchild);
        preorder1(T->rchild);
    }
}
int main()
{
    Btree test=pre_in_creatrtree("ABDGCEFH","DGBAECHF",8);
    preorder1(test);
    return 0;
}