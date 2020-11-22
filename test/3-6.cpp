#include "../lib/head.h"
/*
*/
class equipment
{
public:
    equipment(int p, int a) : price(p),
        ability(a),
        lchild(nullptr),
        rchild(nullptr),
        brother(nullptr),
        parent(nullptr)
    {
    }
    ~equipment()
    {
    }
    equipment* lchild;
    equipment* brother;
    equipment* rchild;
    equipment* parent;

    int price;   //价格
    int ability; //速度值
};
class solution
{
public:
    solution() : poxiao(new equipment(3400, 35)), //破晓
        _n(8)
    {
    }
    ~solution() {}
    void createtree()
    {
        equipment* chuanyungong = new equipment(1100, 10);
        equipment* sujizhiqiang = new equipment(890, 25);
        equipment* chongnengquantao = new equipment(550, 0);
        equipment* leimingqiang = new equipment(450, 0);
        equipment* bishou1 = new equipment(290, 10);
        equipment* bishou2 = new equipment(290, 10);
        equipment* bishou3 = new equipment(290, 10);

        poxiao->lchild = chuanyungong;
        chuanyungong->parent = poxiao;
        sujizhiqiang->parent = poxiao;
        chongnengquantao->parent = poxiao;
        chuanyungong->brother = sujizhiqiang;
        sujizhiqiang->brother = chongnengquantao;

        chuanyungong->lchild = leimingqiang;
        leimingqiang->parent = chuanyungong;
        leimingqiang->brother = bishou1;
        bishou1->parent = chuanyungong;

        sujizhiqiang->lchild = bishou2;
        bishou2->parent = sujizhiqiang;
        bishou2->brother = bishou3;
        bishou3->parent = sujizhiqiang;
    }
    void treetobinarytree() //兄弟变右子树
    {
        stack<equipment*> mystack;
        equipment* temp = poxiao;
        mystack.push(temp);
        for (int i = 0; i < _n; ++i)
        {
            if (temp!=nullptr && temp->brother)
            {
                equipment* t = temp;
                mystack.push(t);
                temp->rchild = temp->brother;
                temp->rchild->parent = temp;
                temp = temp->brother;
                temp->parent->brother = nullptr;
            }
            else
            {
                temp = mystack.top()->lchild;
                mystack.pop();
            }
        }
    }
    void print()//测试
    {
        cout << poxiao->lchild->rchild->price << endl;
    }

private:
    equipment* poxiao;
    int _n;
};
int main()
{
    solution test;
    test.createtree();
    test.treetobinarytree();
    test.print();
    return 0;
}