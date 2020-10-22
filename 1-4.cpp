#include "lib/head.h"

struct listnode
{
    int coef;
    int exp;
    listnode *next;
};
class solution
{
public:
    solution() : _head(new listnode()), _ptr(_head), _size(0)
    {
    }
    ~solution()
    {
        listnode *p = _head->next;
        for (int i = 0; i < _size; ++i)
        {
            listnode *temp = p->next;
            if (p != nullptr)
                delete p;
            p = temp;
        }
    }
    //拷贝构造
    solution &operator=(const solution &a)
    {
        listnode *temp = a._head->next;
        while (temp != nullptr)
        {
            listnode *p = new listnode();
            p->coef = temp->coef;
            p->exp = temp->exp;
            p->next = nullptr;
            temp = temp->next;
            _ptr->next = p;
            _ptr = p;
        }
        _size = a._size;
        return *this;
    }
    void push_back(const int &a, const int &b)
    {
        listnode *p = new listnode();
        p->coef = a;
        p->exp = b;
        _ptr->next = p;
        p->next = nullptr;
        _ptr = p;
        _size++;
    }
    void print()
    {
        if (!empty())
        {
            listnode *p = _head->next;
            for (int i = 1; i <= _size; ++i)
            {
                cout << p->coef << "X" << p->exp << " ";
                p = p->next;
            }
        }
        cout << endl;
    }
    bool empty() { return _head->next == nullptr; }

private:
    listnode *_head;
    int _size;
    listnode *_ptr;
    friend solution operator+(const solution &a,const solution &b);
};
//加法运算符重载
solution operator+(const solution &a,const solution &b)
{
    solution temp;
    int size=min(a._size,b._size);
    listnode *temp1=a._head->next;
    listnode *temp2=b._head->next;
    for(int i=1;i<=size;++i)
    {
        temp.push_back(temp1->coef+temp2->coef,temp1->exp+temp2->exp);
        temp1=temp1->next;
        temp2=temp2->next;
    }
    while(temp1!=nullptr)
    {
        temp.push_back(temp1->coef,temp1->exp);
        temp1=temp1->next;
    }
    while(temp2!=nullptr)
    {
        temp.push_back(temp2->coef,temp2->exp);
        temp2=temp2->next;
    }
    return temp;
}
int main()
{
    solution a1;
    solution a2;
    a1.push_back(5, 0);
    a1.push_back(6, 1);
    a1.print();
    a2 = a1;
    a2.push_back(-10,2);
    a2.print();
    solution a3(a1+a2);
    a3.print();
    return 0;
}