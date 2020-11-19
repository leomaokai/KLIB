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
    equipment *lchild;
    equipment *brother;
    equipment *rchild;
    equipment *parent;

    int price;   //价格
    int ability; //速度值
};
class solution
{
public:
    solution() : _root(new equipment(3400, 35)),//破晓
                 _n(1)
    {
    }
    ~solution() {}
    void createtree() {}
    void treetobinarytree() {}
    void start() {}

private:
    equipment *_root;
    int _n;
};