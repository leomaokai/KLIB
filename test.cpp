#include "lib/test.h"
#include<queue>
class test1
{
public:
    test1()
    {
        cout << "test1()" << endl;
    }
    ~test1()
    {
        cout << "~test1()" << endl;
    }
};
class test2 : public test1
{
public:
    test2()
    {
        c.push(test());
        cout << "test2()" << endl;
    }
    ~test2()
    {
        cout << "~test2()" << endl;
    }

private:
    test a;
    queue<test> c;
};
int main()
{
    test2 b;
    queue<test> a;
    a.push(test());
    return 0;
}