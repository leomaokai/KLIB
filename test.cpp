#include "lib/test.h"
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
        cout << "test2()" << endl;
    }
    ~test2()
    {
        cout << "~test2()" << endl;
    }

private:
    test a;
};
int main()
{
    test2 b;
    return 0;
}