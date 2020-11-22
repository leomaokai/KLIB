//基于邻接矩阵的图
#ifndef GRAPH_H
#define GRAPH_H

#include "head.h"
using T = char;
class mygraph
{
public:
    mygraph(int n = 0, int e = 0, bool f = false) : _n(n),
                                                    _e(e),
                                                    vex(new T[_n]()),
                                                    edge(new int *[_n]()),
                                                    flag(f),
                                                    visited(new int[_n]())
    {
        for (int i = 0; i < _n; ++i)
            edge[i] = new int[_n]();
    }
    ~mygraph()
    {
        if (vex != nullptr)
            delete[] vex;
        for (int i = 0; i < _n; ++i)
            if (edge[i] != nullptr)
            {
                delete []edge[i];
            }
        vex = nullptr;
        if (edge != nullptr)
            delete[] edge;
        edge = nullptr;
        if (visited != nullptr)
            delete[] visited;
        visited = nullptr;
    }
    int findvex(const T &a)
    {
        for (int i = 0; i < _n; ++i)
            if (vex[i] == a)
                return i;
        return -1;
    }
    void getvex(const int &i)
    {
        if (i < 0 || i >= _n)
        {
            cout << "error1" << endl;
            return;
        }
        cout << vex[i] << " ";
    }
    void creategraph() //创建邻接表
    {
        cout << "input vex :" << endl; //输入顶点信息
        for (int i = 0; i < _n; ++i)
            cin >> vex[i];
        cout << "input vex to vex and w(1)" << endl; //输入顶点间关系
        int temp = 0;
        T tempvex1;
        T tempvex2;
        int tempweight = 0;
        int e = _e;
        while (e--)
        {
            cin >> tempvex1 >> tempvex2 >> tempweight;
            int i = findvex(tempvex1);
            int j = findvex(tempvex2);
            if (i != -1 && j != -1)
            {
                edge[i][j] = tempweight;
                if (!flag) //无向图
                {
                    edge[j][i] = tempweight;
                }
            }
            else
            {
                cout << "input error" << endl;
                e++;
            }
        }
    }
    void print() //以邻接表的形式打印图
    {
        cout << "output the graph:" << endl;
        for (int i = 0; i < _n; ++i)
        {
            for (int j = 0; j < _n; ++j)
                cout << edge[i][j] << " ";
            cout << endl;
        }
    }
    void clear()
    {
        for (int i = 0; i < _n; ++i)
            visited[i] = 0;
    }

private:
    int _n;       //顶点数
    int _e;       //边数
    T *vex;       //顶点数组
    int **edge;   //邻接矩阵
    bool flag;    //是否为有向图,默认false无向
    int *visited; //是否被访问过
    friend void dfsam(mygraph &g, const int &v);
    friend void bfsam(mygraph &g, const int &v);
};
void dfsam(mygraph &g, const int &v) //深度优先遍历,v顶点开始遍历
{
    if (v < 0 || v >= g._n) //判断v是否在顶点范围内
    {
        cout << "error" << endl;
        return;
    }
    cout << g.vex[v] << " "; //输出并标记访问过
    g.visited[v] = 1;
    for (int w = 0; w < g._n; ++w) //递归
    {
        if (g.edge[v][w] != 0 && g.visited[w] == 0)
            dfsam(g, w);
    }
}
void bfsam(mygraph &g, const int &v) //广度优先遍历,v顶点开始
{
    if (v < 0 || v >= g._n) //判断v是否在顶点范围内
    {
        cout << "error" << endl;
        return;
    }
    queue<T> que;       //使用队列
    que.push(g.vex[v]); //将v顶点入队
    while (!que.empty())
    {
        T u = que.front();     //取队头
        que.pop();             //出队
        int t = g.findvex(u);  //得到对头顶点的下标
        if (g.visited[t] != 1) //如果没有访问过则访问,并将其邻接点入队
        {
            g.visited[t] = 1; //标记为访问过
            cout << u << " ";
            for (int w = 0; w < g._n; ++w)
            {
                if (g.edge[t][w] != 0)  //存在路径
                    que.push(g.vex[w]); //入队
            }
        }
    }
}

#endif