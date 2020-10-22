//顺序表
//元素位置从0开始
#include "head.h"
template <typename T>
class seqlist
{
public:
    seqlist(int size = 10) //构造函数
    {
        _first = new T[size]();
        _last = _first;
        _end = _first + size;
    }
    ~seqlist() //析构函数
    {
        delete[] _first;
    }
    void push_back(const T &val) //向表尾插入元素
    {
        if (full())
            expand();
        *_last++ = val;
    }
    T getval(const int &pos) //返回pos位置的元素
    {
        if (pos < 0 || pos > num() - 1) //判断插入是否合理
        {
            cout << "pos is error" << endl;
            throw "the pos error";
        }
        return _first[pos];
    }
    void insert(const int &pos, const T &val) //在pos位置插入元素val
    {
        if (pos < 0 || pos > size()) //判断插入是否合理
        {
            throw "the pos error";
        }
        //从最后一个元素到pos位置的元素后移一位
        for (int i = size() - 1; i >= pos; --i)
            _first[i + 1] = _first[i];
        _first[pos] = val; //插入元素
        ++_last;
        if (full())
            expand();
    }
    void del(const int &pos) //删除pos位置的元素
    {
        if (pos < 0 || pos > size())
        {
            throw "the pos error";
        }
        //从pos之后的元素向前移动一位
        for (int i = pos; i < num(); ++i)
            _first[i] = _first[i + 1];
        _first[num() - 1] = 0;
        --_last;
    }
    int number(const T &val) //返回元素val的个数
    {
        int count = 0;
        for (int i = 0; i < num(); ++i)
            if (_first[i] == val)
                ++count;
        return count;
    }
    int findval(const int &pos, const T &val) //查找是否有相同的元素,返回表中首次出现的位置
    {
        for (int i = pos; i < size(); ++i)
            if (val == _first[i])
                return i;
        return -1;
    }
    void print()
    {
        if (empty())
            cout << "the sqlist is empty" << endl;
        else
        {
            for (int i = 0; i < num(); ++i)
                cout << _first[i] << " ";
            cout << endl;
        }
    }
    bool full() { return _last == _end; }    //判断是否满
    bool empty() { return _first == _last; } //判断是否为空
    int size() { return _end - _first; }     //返回数组大小
    int num() { return _last - _first; }     //返回元素个数
private:
    T *_first;    //指向第一个元素
    T *_last;     //指向最后一个元素的后继位置
    T *_end;      //指向数组空间的后继位置
    void expand() //扩容
    {
        int _size = _end - _first;
        T *temp = new T[2 * _size](); //二倍动态扩容
        for (int i = 0; i < _size; ++i)
            temp[i] = _first[i];
        delete[] _first;
        _first = temp;
        _last = _first + _size;
        _end = _first + 2 * _size;
    }
};