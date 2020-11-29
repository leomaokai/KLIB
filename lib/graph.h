//基于邻接矩阵的图
#ifndef GRAPH_H
#define GRAPH_H

#include "head.h"
using T = char;
const int inf = 1000; //表示无穷
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
                delete[] edge[i];
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
    void creategraph() //创建邻接矩阵
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
    friend void prim(mygraph &g, const int &v);
    friend void floyd(mygraph &g);
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

void prim(mygraph &g, const int &v)
{
    for (int i = 0; i < g._n; ++i)
    {
        for (int j = 0; j < g._n; ++j)
        {
            int temp = g.edge[i][j];
            if (i == j)
                g.edge[i][j] = 0;
            else if (i != j && g.edge[i][j] == 0)
                g.edge[i][j] = inf;
        }
    }
    bool *s = new bool[g._n]();
    int *lowcost = new int[g._n]();
    int *closest = new int[g._n]();
    s[v] = true;                   //v加入集合u
    for (int i = 0; i < g._n; ++i) //初始化lowcost和closest
    {
        if (i != v)
        {
            lowcost[i] = g.edge[v][i];
            closest[i] = v;
            s[i] = false;
        }
    }
    for (int i = 0; i < g._n; ++i)
    {
        int temp = inf;
        int t = v;
        for (int j = 0; j < g._n; ++j) //在集合V-u中寻找距离集合u最近的顶点t
        {
            if ((!s[j]) && (lowcost[j] < temp))
            {
                t = j;
                temp = lowcost[j];
            }
        }
        if (t == v)
            break;
        s[t] = true;                   //将顶点t加入集合u
        for (int j = 0; j < g._n; ++j) //更新t邻接顶点的lowcost和closest
        {
            if ((!s[j]) && (g.edge[t][j] < lowcost[j]))
            {
                lowcost[j] = g.edge[t][j];
                closest[j] = t;
            }
        }
    }
    cout << "lowcost: " << endl;
    for (int i = 0; i < g._n; ++i)
    {
        cout << lowcost[i] << " ";
    }
    cout << endl;
    cout << "closest: " << endl;
    for (int i = 0; i < g._n; ++i)
    {
        cout << closest[i] << " ";
    }
    cout << endl;
    int sumcost = 0;
    for (int i = 0; i < g._n; ++i)
    {
        sumcost += lowcost[i];
    }
    cout << "sumcost: " << sumcost << endl;

    delete[] s;
    delete[] lowcost;
    delete[] closest;
}

void floyd(mygraph &g)
{
    for (int i = 0; i < g._n; ++i)
    {
        for (int j = 0; j < g._n; ++j)
        {
            int temp = g.edge[i][j];
            if (i == j)
                g.edge[i][j] = 0;
            else if (i != j && g.edge[i][j] == 0)
                g.edge[i][j] = inf;
        }
    }
    int **dist = new int *[g._n](); //记录顶点间距离数组
    for (int i = 0; i < g._n; ++i)
    {
        dist[i] = new int[g._n]();
    }
    int **p = new int *[g._n](); //记录前驱顶点数组
    for (int i = 0; i < g._n; ++i)
    {
        p[i] = new int[g._n]();
    }
    for (int i = 0; i < g._n; ++i)
    {
        for (int j = 0; j < g._n; ++j)
        {
            dist[i][j] = g.edge[i][j];
            if (dist[i][j] < inf && i != j)
                p[i][j] = i; //如果i和j之间有弧,则将j的前驱置位i
            else
                p[i][j] = -1; //如果i和j之间无弧,则将j的前驱置为-1
        }
    }
    for (int k = 0; k < g._n; ++k)
    {
        for (int i = 0; i < g._n; ++i)
        {
            for (int j = 0; j < g._n; ++j)
            {
                //i经k到j的最短路径
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j]; //更新dist[i][j]
                    p[i][j] = p[k][j];                    //更新j的前驱为k
                }
            }
        }
    }
    cout << "v and u distance:" << endl; //两个点之间的最短距离
    for (int i = 0; i < g._n; ++i)
    {
        for (int j = 0; j < g._n; ++j)
            cout << dist[i][j] << " ";
        cout << endl;
    }
    cout << "pre v:" << endl; //每个点的前驱顶点
    for (int i = 0; i < g._n; ++i)
    {
        for (int j = 0; j < g._n; ++j)
            cout << p[i][j] << " ";
        cout << endl;
    }
    for (int i = 0; i < g._n; ++i)
        if (dist[i] != nullptr)
        {
            delete[] dist[i];
        }
    for (int i = 0; i < g._n; ++i)
        if (p[i] != nullptr)
        {
            delete[] p[i];
        }
    delete[] dist;
    delete[] p;
}
#endif