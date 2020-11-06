#include "../lib/head.h"

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
        listnode *temp = nullptr;
        while (p != nullptr)
        {
            temp = p->next;
            delete p;
            p = temp;
        }
    }
    solution(const solution &a) : _head(new listnode()), _ptr(_head)
    {
        _size = a._size;
        listnode *temp1 = a._head->next;
        while (temp1 != nullptr)
        {
            listnode *p = new listnode();
            p->coef = temp1->coef;
            p->exp = temp1->exp;
            p->next = nullptr;
            temp1 = temp1->next;
            _ptr->next = p;
            _ptr = p;
        }
    }
    //赋值构造
    solution &operator=(const solution &a)
    {
        listnode *p = this->_head->next;
        listnode *temp = nullptr;
        while (p != nullptr)
        {
            temp = p->next;
            delete p;
            p = temp;
        }
        this->_ptr = this->_head;
        this->_size = a._size;
        listnode *temp1 = a._head->next;
        while (temp1 != nullptr)
        {
            listnode *p = new listnode();
            p->coef = temp1->coef;
            p->exp = temp1->exp;
            p->next = nullptr;
            temp1 = temp1->next;
            this->_ptr->next = p;
            this->_ptr = p;
        }
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
            while (p != nullptr)
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
    friend solution operator+(const solution &a, const solution &b);
};
//加法运算符重载

solution operator+(const solution &a, const solution &b)
{
    solution temp;
    listnode *temp1 = a._head->next;
    listnode *temp2 = b._head->next;
    while (temp1 != nullptr && temp2 != nullptr)
    {
        temp.push_back(temp1->coef + temp2->coef, temp1->exp);
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    while (temp1 != nullptr)
    {
        temp.push_back(temp1->coef, temp1->exp);
        temp1 = temp1->next;
    }
    while (temp2 != nullptr)
    {
        temp.push_back(temp2->coef, temp2->exp);
        temp2 = temp2->next;
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
    a2.push_back(10, 0);
    a2.print();
    a2 = a1;
    a2.print();
    solution a3(a1 + a2);
    a3.print();
    solution a4;
    a4 = a3 + a1;
    a4.print();
    return 0;
}