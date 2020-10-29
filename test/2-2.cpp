#include "../lib/head.h"
//利用链栈,将xxxx秒转换为n天m小时t分钟q秒

class listnode
{
public:
    int data;
    string deno;
    listnode *next;
    listnode *pre;
};
class liststack
{
public:
    liststack() : _stack(new listnode()), _top(_stack), _size(0)
    {
    }
    ~liststack()
    {
        while (!empty())
        {
            listnode *p = _top->pre;
            delete _top;
            _top = p;
        }
        _size = 0;
    }
    void push(const int &val, const string &str)
    {
        listnode *p = new listnode();
        p->data = val;
        p->deno = str;
        _top->next = p;
        p->pre = _top;
        _top = p;
        _size++;
    }
    void pop()
    {
        if (!empty())
        {
            listnode *p = _top->pre;
            delete _top;
            _top = p;
            --_size;
        }
    }
    listnode *top()
    {
        if (!empty())
            return _top;
    }
    bool empty() { return _top == _stack; }
    int size() { return _size; }

private:
    listnode *_stack;
    listnode *_top;
    int _size;
};
void solution(int second)
{
    cout << "seconds =" << second << endl;
    liststack mstack1;
    int n = second / 86400;
    mstack1.push(n, "day");
    second %= 86400;
    int m = second / 3600;
    mstack1.push(m, "hour");
    second %= 3600;
    int t = second / 60;
    mstack1.push(t, "minute");
    second %= 60;
    mstack1.push(second, "second");
    liststack mstack2;
    while (!mstack1.empty())
    {
        listnode *p = mstack1.top();
        mstack2.push(p->data,p->deno);
        mstack1.pop();
    }
    while (!mstack2.empty())
    {
        listnode *p = mstack2.top();
        cout<<p->data<<" "<<p->deno<<" ";
        mstack2.pop();
    }
    cout << endl;
}
int main()
{
    solution(1000);
    solution(1000000);
    return 0;
}