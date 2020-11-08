#include <iostream>
using namespace std;
/*
输入顶点的个数,然后按顶点标号(从0开始)创建邻接表,-1表示空,即没有邻接点了

0--first-->1--next-->2--next-->-1
1--first-->2--next-->3--next-->-1
2--first-->1--next-->0--next-->-1
3--first-->2--next-->1--next-->-1

*/
void solution()
{
    int n = 0; //顶点的个数
    int m = 0; //邻接点的标号
    cout << "please input n" << endl;
    cin >> n;
    int count[n]{};
    for (int i = 0; i < n; ++i)
    {
        cout << i << "--first-->";
        while (1)
        {
            cin >> m;
            if (m != -1)
            {
                cout << m << "--next-->";
                count[m]++;
            }
            else
                break;
        }
    }
    for (int i = 0; i < n; ++i)
        cout << count[i] << endl;
}
int main()
{
    solution();
    return 0;
}