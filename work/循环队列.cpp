#include <iostream>
using namespace std;
class Queue //循环队列
{
public:
    Queue(int size = 5)
    {
        _pQue = new int[size]();
        _front = 0;
        _rear = 0;
        _size = size;
    }
    ~Queue()
    {
        delete[] _pQue;
        _pQue = nullptr;
    }
    void push(int val) //入队
    {
        if (full())
            resize();
        _pQue[_rear] = val;
        _rear = (_rear + 1) % _size;
    }
    void pop() //出队
    {
        if (empty())
            return;
        _front = (_front + 1) % _size;
    }
    bool full() { return (_rear + 1) % _size == _front; }
    bool empty() { return _front == _rear; }
    void print()
    {
        if (empty())
            return;
        int f = _front;
        int r = _rear;
        while (f % _size != r)
        {
            cout << _pQue[f] << " ";
            f = (f + 1) % _size;
        }
        cout << endl;
    }

private:
    int *_pQue;
    int _front; //指向队头
    int _rear;  //指向队尾
    int _size;  //空间

    void resize() //二倍扩容
    {
        int *ptmp = new int[_size * 2]();
        int index = 0;
        for (int i = _front; i != _rear; i = (i + 1) % _size)
        {
            ptmp[index++] = _pQue[i];
        }
        delete[] _pQue;
        _pQue = ptmp;
        _front = 0;
        _rear = index;
        _size *= 2;
    }
};
int main()
{
    Queue que;
    for (int i = 0; i < 15; ++i) //入队15个随机数
        que.push(rand() % 10 + 1);
    que.print();  //打印
    for (int i = 0; i < 5; ++i) //前5个数出队
        que.pop();
    que.print(); //打印
    return 0;
}