//银行业务
#include "../lib/queue.h"
template <typename T>
class bank
{
public:
    bank();
    ~bank();
    void show_menu();
    void getoffwork();
    void takenumber();
    void handlebusiness();
    void showbusiness();

private:
    Queue<T> mqueue;
    int _count;
    int _num;
};
int main()
{
    bank<int> test;
    int choice = 0;
    while (true)
    {
        test.show_menu();
        cout << "input your choice" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0: //取号
            test.takenumber();
            break;
        case 1: //办理
            test.handlebusiness();
            break;
        case 2: //查看
            test.showbusiness();
            break;
        case 3: //下班
            test.getoffwork();
            break;
        default:
            system("cls");
            break;
        }
    }
    return 0;
}
template <typename T>
bank<T>::bank() : _count(0), _num(0)
{
}
template <typename T>
bank<T>::~bank()
{
}
/*
0.取号：编号增1，加入到排队的队列中；判断队列是否满；并打印显示自己的编号和排第几。
1.办理；取出排在最前面的编号，让其办理业务，并将其从队列中删除。
2.查看；列出从队头到队尾的所有编号
3.下班：退出运行，输出队列中剩下的编号和已经办理完成的编号数量。
*/
template <typename T>
void bank<T>::show_menu()
{
    cout << endl;
    cout << "*********  Banking business simulation system  **********" << endl;
    cout << "*************  0.Take a number  *************************" << endl;
    cout << "*************  1.Handle the business  *******************" << endl;
    cout << "*************  2.show the business  *********************" << endl;
    cout << "*************  3.get off work  **************************" << endl;
    cout << endl;
}
template <typename T>
void bank<T>::takenumber()
{
    mqueue.push(++_count);
    cout << "your number :" << _count << endl;
    cout << "your rank :" << mqueue.number() << endl;
}
template <typename T>
void bank<T>::handlebusiness()
{
    if (mqueue.empty())
        cout << "no one" << endl;
    else
    {
        cout << "please " << mqueue.front() << " to handle business" << endl;
        mqueue.pop();
        ++_num;
        cout << "OK" << endl;
    }
}
template <typename T>
void bank<T>::showbusiness()
{
    cout << "now have number:" << endl;
    mqueue.print();
}
template <typename T>
void bank<T>::getoffwork()
{
    cout << _num << " business have done" << endl;
    cout << "now no handle business:" << endl;
    mqueue.print();
    cout << "thanks" << endl;
    exit(0);
}