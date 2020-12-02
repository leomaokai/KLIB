#include "head.h"
class test
{
public:
    test():_n(5)
    {
    }
    ~test()
    {
    }
    void testdigui()
    {
        while (_n!=0)
        {
            --_n;
            cout << "hello" << endl;
            testdigui();
        }
    }
    int _n;
};