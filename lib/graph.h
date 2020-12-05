//mygraph基于邻接矩阵
//listgraph基于邻接表

#ifndef GRAPH_H
#define GRAPH_H

#include "head.h"
using T = int;
const int inf = 1000; //表示无穷
class mygraph;
class listgraph;

//基于邻接矩阵
class mygraph
{
public:
    mygraph(int n, int e, bool f);
    ~mygraph();
    int findvex(const T &a);
    void getvex(const int &i);
    void creategraph(); //创建邻接矩阵
    void print();       //以邻接表的形式打印图
    void clear();
    void getoutdegree();
    void getindegree();

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
//基于邻接表
class listgraph
{
public:
    listgraph(int n, int e, bool f);
    ~listgraph();
    void createlistgraph();
    void print();
    void reprint();
    int findvex(const char &ch);
    void getindegree();
    void getoutdegree();
    void listdfs();

private:
    struct listnode
    {
        int to;
        int weight;
        listnode *next;
    };
    struct vexnode
    {
        char v;
        listnode *first;
    };
    vexnode *vexarry;
    vexnode *revexarry;
    int vexnum;
    int edgenum;
    bool flag;
};
mygraph::mygraph(int n = 0, int e = 0, bool f = false) : _n(n),
                                                         _e(e),
                                                         vex(new T[_n]()),
                                                         edge(new int *[_n]()),
                                                         flag(f),
                                                         visited(new int[_n]())
{
    for (int i = 0; i < _n; ++i)
        edge[i] = new int[_n]();
}
mygraph::~mygraph()
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
int mygraph::findvex(const T &a)
{
    for (int i = 0; i < _n; ++i)
        if (vex[i] == a)
            return i;
    return -1;
}
void mygraph::getvex(const int &i)
{
    if (i < 0 || i >= _n)
    {
        cout << "error1" << endl;
        return;
    }
    cout << vex[i] << " ";
}
void mygraph::creategraph() //创建邻接矩阵
{
    cout << "input vex :" << endl; //输入顶点信息
    for (int i = 0; i < _n; ++i)
        cin >> vex[i];
    cout << "input vex to vex and w(1)" << endl; //输入顶点间关系
    int temp = 0;
    T tempvex1;
    T tempvex2;
    int tempweight;
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
void mygraph::print() //以邻接表的形式打印图
{
    cout << "output the graph:" << endl;
    for (int i = 0; i < _n; ++i)
    {
        for (int j = 0; j < _n; ++j)
            cout << edge[i][j] << " ";
        cout << endl;
    }
}
void mygraph::clear()
{
    for (int i = 0; i < _n; ++i)
        visited[i] = 0;
}
void mygraph::getoutdegree()
{
    int *count = new int[_n]();
    for (int i = 0; i < _n; ++i)
    {
        for (int j = 0; j < _n; ++j)
        {
            if (edge[i][j] != 0)
                count[i]++;
        }
    }
    for (int i = 0; i < _n; ++i)
        cout << count[i] << " ";
    cout << endl;
    delete[] count;
}
void mygraph::getindegree()
{
    int *count = new int[_n]();
    for (int j = 0; j < _n; ++j)
    {
        for (int i = 0; i < _n; ++i)
        {
            if (edge[i][j] != 0)
                count[j]++;
        }
    }
    for (int i = 0; i < _n; ++i)
        cout << count[i] << " ";
    cout << endl;
    delete[] count;
}
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
        cout << g.vex[closest[i]] << " ";
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
listgraph::listgraph(int n = 0, int e = 0, bool f = false) : vexnum(n),
                                                             edgenum(e),
                                                             vexarry(new vexnode[vexnum]()),
                                                             revexarry(new vexnode[vexnum]()),
                                                             flag(f)
{
}
listgraph::~listgraph()
{
    for (int i = 0; i < vexnum; ++i)
    {
        listnode *tempnode1 = vexarry[i].first;
        listnode *tempnode2 = nullptr;
        listnode *tempnode3 = revexarry[i].first;
        while (tempnode1 != nullptr)
        {
            tempnode2 = tempnode1->next;
            delete tempnode1;
            tempnode1 = tempnode2;
        }
        while (tempnode3 != nullptr)
        {
            tempnode2 = tempnode3->next;
            delete tempnode3;
            tempnode3 = tempnode2;
        }
    }
}
void listgraph::createlistgraph()
{
    cout << "input vex:" << endl;
    for (int i = 0; i < vexnum; ++i)
    {
        vexarry[i].first = nullptr;
        revexarry[i].first = nullptr;
        cin >> vexarry[i].v;
        revexarry[i].v = vexarry[i].v;
    }
    cout << "input vex to vex and w(1)" << endl;
    char tempvex1;
    char tempvex2;
    int tempw;
    int e = edgenum;
    while (e--)
    {
        cin >> tempvex1 >> tempvex2 >> tempw;
        int i = findvex(tempvex1);
        int j = findvex(tempvex2);
        if (i != -1 && j != -1)
        {
            listnode *tempnode = new listnode();
            tempnode->to = j;
            tempnode->weight = tempw;
            tempnode->next = vexarry[i].first;
            vexarry[i].first = tempnode;

            listnode *retempnode = new listnode();
            retempnode->to = i;
            retempnode->weight = tempw;
            retempnode->next = revexarry[j].first;
            revexarry[j].first = retempnode;

            if (!flag)
            {
                listnode *tempnode1 = new listnode();
                tempnode1->to = i;
                tempnode1->weight = tempw;
                tempnode1->next = vexarry[j].first;
                vexarry[j].first = tempnode1;

                listnode *retempnode1 = new listnode();
                retempnode1->to = j;
                retempnode1->weight = tempw;
                retempnode1->next = revexarry[i].first;
                revexarry[i].first = retempnode1;
            }
        }
        else
        {
            cout << "input errot" << endl;
            e++;
        }
    }
}
void listgraph::print()
{
    cout << "output the graph:" << endl;
    for (int i = 0; i < vexnum; ++i)
    {
        listnode *tempnode = vexarry[i].first;
        cout << vexarry[i].v << "--first-->";
        while (tempnode != nullptr)
        {
            cout << "(" << tempnode->weight << ")" <<vexarry[tempnode->to].v << "--next-->";
            tempnode = tempnode->next;
        }
        cout << "nullptr" << endl;
    }
}
void listgraph::reprint()
{
    cout << "output reverse listgraph:" << endl;
    for (int i = 0; i < vexnum; ++i)
    {
        listnode *tempnode = revexarry[i].first;
        cout << revexarry[i].v << "--first-->";
        while (tempnode != nullptr)
        {
            cout << "(" << tempnode->weight << ")" << tempnode->to << "--next-->";
            tempnode = tempnode->next;
        }
        cout << "nullptr" << endl;
    }
}
int listgraph::findvex(const char &ch)
{
    for (int i = 0; i < vexnum; ++i)
    {
        if (ch == vexarry[i].v)
            return i;
    }
    return -1;
}
void listgraph::getindegree()
{
    int *count = new int[vexnum]();
    listnode *tempnode = nullptr;
    for (int i = 0; i < vexnum; ++i)
    {
        tempnode = revexarry[i].first;
        while (tempnode != nullptr)
        {
            count[i]++;
            tempnode = tempnode->next;
        }
    }
    for (int i = 0; i < vexnum; ++i)
        cout << count[i] << " ";
    cout << endl;
    delete[] count;
}
void listgraph::getoutdegree()
{
    int *count = new int[vexnum]();
    listnode *tempnode = nullptr;
    for (int i = 0; i < vexnum; ++i)
    {
        tempnode = vexarry[i].first;
        while (tempnode != nullptr)
        {
            count[i]++;
            tempnode = tempnode->next;
        }
    }
    for (int i = 0; i < vexnum; ++i)
        cout << count[i] << " ";
    cout << endl;
    delete[] count;
}
void listgraph::listdfs()
{
    //if (start >= vexnum || start < 0)
    //    return;
    stack<int> tempstack;
    int temp = 0;
    listnode *tempnode = nullptr;
    bool *visited = new bool[vexnum]();
    tempstack.push(temp);
    while (!tempstack.empty())
    {
        int stacktop = tempstack.top();
        if (!visited[stacktop])
        {
            cout << vexarry[stacktop].v << " ";
            visited[stacktop] = true;
        }
        tempnode = vexarry[stacktop].first;
        while (tempnode != nullptr)
        {
            temp = tempnode->to;
            if (!visited[temp])
            {
                tempstack.push(temp);
                break;
            }
            tempnode = tempnode->next;
        }
        if (tempnode == nullptr)
            tempstack.pop();
    }
    cout << endl;
    delete[] visited;
}
#endif