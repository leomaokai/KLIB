#include "../lib/liststack.h"
//将十进制数转化为d进制数
//用链栈实现
void solution(int val, const int &d)
{
    liststack<int> mstack;
    while (val)
    {
        int ret = 0;
        ret = val % d;//求余数
        val /= d;
        mstack.push(ret);//将余数压入栈
    }
    while (!mstack.empty())
    {
        int ret = mstack.top();//栈顶元素赋值
        mstack.pop();//栈顶出栈
        char ch;
        if (ret >= 10)//ret>=10,则输出abcdef
        {
            ch = ret + 55;//ascii转换
            cout << ch;
            continue;
        }
        cout << ret;
    }
    cout << endl;
}
int main()
{
    solution(10, 2);
    solution(10, 8);
    solution(10, 16);
    solution(1024, 2);
    solution(1024, 8);
    solution(1024, 16);
    solution(487, 2);
    solution(487, 8);
    solution(487, 16);
    return 0;
}