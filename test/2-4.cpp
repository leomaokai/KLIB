#include "../lib/queue.h"
void solution()
{
    Queue<char> mqueue;        //用队列
    cout << "input n" << endl; //输入字符的个数n
    int n = 0;
    cin >> n;
    char ch = '0';
    for (int i = 0; i < n; ++i)
    {
        cin >> ch;
        mqueue.push(ch); //入队
    }
    while (mqueue.front() == mqueue.rear()) //队头与队尾相同
    {
        mqueue.pop();      //队头字符出队
        mqueue.pop_bcak(); //队尾字符出队
        //如果只剩一个字符或队列为空,则字符串为回文
        if (mqueue.number() == 1 || mqueue.empty())
        {
            cout << "yes" << endl;
            return;
        }
    }
    //否则不是回文
    cout << "no" << endl;
    return;
}
int main()
{
    solution();
    return 0;
}