#ifndef LISTSTACK_H
#define LISTSTACK_H
#include "head.h"
//链栈
template <typename T>
class listnode
{
public:
    T data;
    listnode<T> *next;
    listnode<T> *pre;
};
template <typename T>
class liststack
{
public:
    liststack() : _stack(new listnode<T>()), _top(_stack), _size(0)
    {
    }
    ~liststack()
    {
        while (!empty())
        {
            listnode<T> *p = _top->pre;
            delete _top;
            _top = p;
        }
        _size = 0;
    }
    void push(const T &val)
    {
        listnode<T> *p = new listnode<T>();
        p->data = val;
        _top->next = p;
        p->pre = _top;
        _top = p;
        _size++;
    }
    void pop()
    {
        if (!empty())
        {
            listnode<T> *p = _top->pre;
            delete _top;
            _top = p;
            --_size;
        }
    }
    T top()
    {
        if (!empty())
            return _top->data;
    }
    bool empty() { return _top == _stack; }
    int size() { return _size; }

private:
    listnode<T> *_stack;
    listnode<T> *_top;
    int _size;
};
#endif