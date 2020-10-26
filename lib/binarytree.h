#ifndef BINARYTREE_H
#define BINARYTREE_H
//二叉树
#include"head.h"
template<typename T>
struct treenode
{
    T data;
    treenode<T> *lchild;
    treenode<T> *rchild;
    treenode<T> *father;
};
template<typename T>
class binarytree
{
    public:
    binarytree():_root(new treenode<T>()),n(0)
    {}
    ~binarytree(treenode<T> *p)
    {
        if(p==nullptr)
            return;
        ~binarytree(_root->lchild);
        ~binarytree(_root->rchild);
        delete _root;
    }
    private:
    treenode<T> *_root;//树根
    int n;//结点数
};