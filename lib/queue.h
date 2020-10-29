#include "head.h"
template <typename T>
class Queue //循环队列
{
public:
    Queue(int size = 5) : _pQue(new T[size]()), _front(0), _rear(0), _size(size)
    {
    }
    ~Queue()
    {
        delete[] _pQue;
        _pQue = nullptr;
    }
    void push(T val) //入队
    {
        if (full())
            resize();
        _pQue[_rear] = val;
        _rear = (_rear + 1) % _size;
    }
    void pop() //队头出队
    {
        if (empty())
            return;
        _front = (_front + 1) % _size;
    }
    void pop_bcak() //队尾出队
    {
        if (empty())
            return;
        _rear = (_rear - 1) % _size;
    }
    bool full()
    {
        return (_rear + 1) % _size == _front;
    }
    bool empty() { return _front == _rear; }
    T front() { return _pQue[_front]; }
    T rear() { return _pQue[_rear - 1]; }
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
    int number()
    {
        int ret = _rear - _front;
        if (ret >= 0)
            return ret;
        else
            return ret + _size;
    }

private:
    T *_pQue;
    int _front; //指向队头
    int _rear;  //指向队尾
    int _size;  //空间

    void resize() //二倍扩容
    {
        T *ptmp = new T[_size * 2]();
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