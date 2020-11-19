#ifndef BINARYTREE_H
#define BINARYTREE_H
//二叉树
#include "head.h"
// int char 两种版本,代码大致相同,唯一区别是补充叶子的类型不同
// 创建一棵二叉树需要先将二叉树补充叶子,然后按先序输入  : binarytree<int> test1;//创建普通二叉树
// 创建一棵哈夫曼树需要先输入叶子的个数,再输入其data与weight  : binarytree<int> test2(5);//创建有5个叶子的哈夫曼树
template <typename T>
class binarytree
{
private:
    struct treenode
    {
        T data;
        int weight;
        treenode *lchild;
        treenode *rchild;
        treenode *parent;
        vector<int> bit;
        bool flag;
    };

public:
    static const char nullchar = '`';
    static const int nullint = -1;
    static const int MAXVALUE = 100;
    binarytree() : _root(new treenode()), _n(0), _l(0)
    {
        _mstack.push(_root); //将根结点入栈,用于创建树
    }
    binarytree(int l) : _l(l), huffnode(new treenode *[2 * l - 1]())
    {
        for (int i = 0; i < 2 * _l - 1; ++i)
            huffnode[i] = new treenode();
        _root = huffnode[2 * _l - 2];
    }
    ~binarytree() //析构函数
    {
        if (_root != nullptr)
        {
            stack<treenode *> mstack;
            mstack.push(_root);
            while (!mstack.empty())
            {
                treenode *p = mstack.top();
                mstack.pop();
                if (p->lchild != nullptr)
                    mstack.push(p->lchild);
                if (p->rchild != nullptr)
                    mstack.push(p->rchild);
                delete p;
            }
        }
        delete[] huffnode;
        _root = nullptr;
    }
    void createtree();                   //创建二叉树
    void preorder();                     //先序遍历
    void inorder();                      //中序遍历
    void postorder();                    //后序遍历,将先序遍历过程中左右子树遍历顺序交换
    void levelorder();                   //层次遍历用队列实现
    void createhuffmantree();            //创建哈夫曼树
    int sizetree() { return _n; }        //二叉树顶点个数
    bool emptytree() { return _n == 0; } //判断二叉树是否为空
    int getrootw() { return _root->weight; }
    int sizeleft() { return _l; } //求叶子数
    int depth();                  //求深度

private:
    treenode *_root;           //根结点
    stack<treenode *> _mstack; //创建二叉树的栈
    treenode **huffnode;
    int _n; //结点个数
    int _l; //叶子数
};
template <typename T>
void binarytree<T>::createtree() //创建二叉树
{
    cout << "input val:" << endl;
    T temp;
    treenode *p;
    int count = 0;
    while (!_mstack.empty())
    {
        cin >> temp;
        p = _mstack.top(); //先将栈顶赋值
        _mstack.pop();
        p->data = temp;
        if ((sizeof(T) == sizeof(int) && temp == nullint) || (sizeof(T) == sizeof(char) && temp == nullchar)) //如果输入#说明结点是叶子,则不需要new孩子结点
        {
            count++;
            if (count == 2) //连续输入两个非结点标志说明前面一个结点是叶子
            {
                _l++;
                p->parent->flag = true;
                count = 0;
            }
            continue;
        }
        else //否则new孩子结点
        {
            count = 0;
            _n++; //结点数加1
            p->rchild = new treenode();
            p->lchild = new treenode();
            p->rchild->parent = p;
            p->lchild->parent = p;
            p->rchild->flag = false;
            p->lchild->flag = false;
        }
        _mstack.push(p->rchild); //先将右结点入栈
        _mstack.push(p->lchild); //再将左结点入栈,这样左孩子会先出栈,先赋值
    }
}
template <typename T>
void binarytree<T>::preorder() //先序遍历
{
    cout << "preorder :" << endl;
    if (_root != nullptr)
    {
        stack<treenode *> mstack;
        mstack.push(_root);
        while (!mstack.empty())
        {
            treenode *p = mstack.top();
            mstack.pop(); //栈顶出栈
            if ((sizeof(T) == sizeof(int) && p->data != nullint) || (sizeof(T) == sizeof(char) && p->data != nullchar))
                cout << p->data << " "; //输出栈顶元素
            if (p->rchild != nullptr)
                mstack.push(p->rchild); //先序遍历先将右孩子入栈
            if (p->lchild != nullptr)
                mstack.push(p->lchild); //再将左孩子入栈
        }
    }
    cout << endl;
}
template <typename T>
void binarytree<T>::inorder() //中序遍历
{
    cout << "inorder :" << endl;
    if (_root != nullptr)
    {
        stack<treenode *> mstack;
        mstack.push(_root);
        treenode *p = mstack.top();
        p = p->lchild;
        while (!mstack.empty() || p != nullptr)
        {
            while (p != nullptr)
            {
                mstack.push(p); //中序遍历先将左孩子全部入栈
                p = p->lchild;
            }
            if (!mstack.empty()) //然后输出左孩子,左孩子出栈,右孩子入栈
            {
                p = mstack.top();
                mstack.pop();
                if ((sizeof(T) == sizeof(int) && p->data != nullint) || (sizeof(T) == sizeof(char) && p->data != nullchar))
                    cout << p->data << " ";
            }
            p = p->rchild;
        }
    }
    cout << endl;
}
template <typename T>
void binarytree<T>::postorder() //后序遍历,将先序遍历过程中左右子树遍历顺序交换
{
    cout << "postorder :" << endl;
    if (_root != nullptr)
    {
        stack<treenode *> mstack1;
        stack<treenode *> mstack2;
        mstack1.push(_root);
        while (!mstack1.empty())
        {
            treenode *p = mstack1.top();
            mstack1.pop(); //栈顶出栈
            if ((sizeof(T) == sizeof(int) && p->data != nullint) || (sizeof(T) == sizeof(char) && p->data != nullchar))
                mstack2.push(p); //先将结点保存到另一个栈中
            if (p->lchild != nullptr)
                mstack1.push(p->lchild); //后序遍历先将左孩子入栈
            if (p->rchild != nullptr)
                mstack1.push(p->rchild); //再将右孩子入栈
        }
        while (!mstack2.empty()) //输出结果
        {
            treenode *p = mstack2.top();
            mstack2.pop();
            cout << p->data << " ";
        }
        cout << endl;
    }
}
template <typename T>
void binarytree<T>::levelorder() //层次遍历用队列实现
{
    cout << "levelorder :" << endl;
    if (_root != nullptr)
    {
        queue<treenode *> mque;
        treenode *p = nullptr;
        mque.push(_root);
        while (!mque.empty())
        {
            p = mque.front();
            mque.pop();
            if ((sizeof(T) == sizeof(int) && p->data != nullint) || (sizeof(T) == sizeof(char) && p->data != nullchar))
                cout << p->data << " ";
            if (p->lchild != nullptr)
                mque.push(p->lchild);
            if (p->rchild != nullptr)
                mque.push(p->rchild);
        }
    }
    cout << endl;
}
template <typename T>
void binarytree<T>::createhuffmantree()
{

    for (int i = 0; i < _l; ++i) //初始化叶子
    {
        cout << "input val and weigth:" << endl;
        cin >> huffnode[i]->data >> huffnode[i]->weight;
        huffnode[i]->flag=true;
    }
    int m1 = 0, m2 = 0, x1 = 0, x2 = 0;
    for (int i = 0; i < _l - 1; ++i) //构造哈夫曼树
    {
        m1 = m2 = MAXVALUE;
        x1 = x2 = 0;
        for (int j = 0; j < _l + i; ++j)
        {
            if (huffnode[j]->weight < m1 && huffnode[j]->parent == nullptr)
            {
                m2 = m1;
                x2 = x1;
                m1 = huffnode[j]->weight;
                x1 = j;
            }
            else if (huffnode[j]->weight < m2 && huffnode[j]->parent == nullptr)
            {
                m2 = huffnode[j]->weight;
                x2 = j;
            }
        }
        //设置新结点
        huffnode[x1]->parent = huffnode[_l + i];
        huffnode[x2]->parent = huffnode[_l + i];
        huffnode[_l + i]->weight = m1 + m2;
        if (sizeof(T) == sizeof(int))
            huffnode[_l + i]->data = 0;
        else
            huffnode[_l + i]->data = '0';
        huffnode[_l + i]->lchild = huffnode[x1];
        huffnode[_l + i]->rchild = huffnode[x2];
    }
    cout << "huffmancode:" << endl;
    for (int i = 0; i < _l; ++i)
    {
        treenode *temp = huffnode[i]->parent;
        treenode *temp2 = huffnode[i];
        while (temp != nullptr)
        {
            if (temp->lchild == temp2)
                huffnode[i]->bit.push_back(0);
            else
                huffnode[i]->bit.push_back(1);
            temp2 = temp;
            temp = temp->parent;
        }
        cout << huffnode[i]->data << ":";
        for (vector<int>::iterator it = huffnode[i]->bit.end(); it != huffnode[i]->bit.begin(); --it)
            cout << *(it - 1) << " ";
        cout << endl;
    }
}
template <typename T>
int binarytree<T>::depth() //先序遍历到叶子从叶子寻找父亲,记录深度
{
    int count = 1;//临时记录每个叶子的深度
    int d = 0;//记录最高深度
    if (_root != nullptr)
    {
        stack<treenode *> mstack;
        mstack.push(_root);
        while (!mstack.empty())
        {
            treenode *p = mstack.top();
            mstack.pop(); //栈顶出栈
            if (p->flag)  //p结点为叶子
            {
                treenode *p2 = p->parent;
                while (p2 != nullptr) //若存在父亲,则深度++
                {
                    count++;
                    p2 = p2->parent;
                }
                if (count > d)
                    d = count;
                count = 1;
            }
            if (p->rchild != nullptr)
                mstack.push(p->rchild); //先序遍历先将右孩子入栈
            if (p->lchild != nullptr)
                mstack.push(p->lchild); //再将左孩子入栈
        }
    }
    return d;
}
#endif