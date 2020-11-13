#include <iostream>
using namespace std;
/*

0--first-->1--next-->2--next-->nullptr
1--first-->2--next-->3--next-->nullptr
2--first-->1--next-->0--next-->nullptr
3--first-->2--next-->1--next-->nullptr

*/
class graphtest
{
public:
    graphtest(int n) : _n(n), graphhead(new head[_n]()) //构造函数
    {
    }
    ~graphtest() //析构函数
    {
        for (int i = 0; i < _n; ++i)
        {
            listnode* temp = graphhead[i].first;
            while (temp != nullptr) //链表删除方式进行delete
            {
                temp = graphhead[i].first->next;
                delete graphhead[i].first;
                graphhead[i].first = temp;
            }
        }
        delete[] graphhead; //delete数组
    }
    void insertuv(const int& u, const int& v) //边的插入
    {
        listnode* temp = new listnode(); //链表头结点插入方式
        temp->next = graphhead[u].first;
        temp->to = v;
        graphhead[u].first = temp;
    }
    void printgraph() //打印邻接表
    {
        for (int i = 0; i < _n; ++i)
        {
            listnode* temp = graphhead[i].first;
            cout << i << "--first-->";
            while (temp != nullptr)
            {
                cout << temp->to << "--next--> ";
                temp = temp->next;
            }
            cout << "nullptr" << endl;
        }
    }
    void solution(); //解题函数
private:
    struct listnode //邻接点结构体
    {
        int to;
        listnode* next;
    };
    struct head //顶点数组结构体
    {
        //int data;
        listnode* first;
    };
    int _n;          //顶点数
    head* graphhead; //顶点数组
};
int main()
{
    int n = 0;
    int e = 0;
    cout << "input n and e" << endl; //n为顶点数,e为边数
    cin >> n >> e;
    graphtest test(n);
    int u = 0;
    int v = 0;
    for (int i = 0; i < e; ++i)
    {
        cout << "input u v" << endl; //u-->v
        cin >> u >> v;
        test.insertuv(u, v);
    }
    test.printgraph();
    test.solution();

    return 0;
}
void graphtest::solution()
{
    int* arry = new int[_n]();              //存放入度的数组
    for (int i = 0; i < _n; ++i) //遍历邻接表
    {
        listnode* temp = (listnode*)graphhead[i].first;
        while (temp != nullptr)
        {
            int t = temp->to;
            arry[t]++; //t顶点入度加1
            temp = temp->next;
        }
    }
    for (int i = 0; i < _n; ++i) //打印结果
        cout << arry[i] << " ";
    cout << endl;
    delete[]arry;
}
