#include "../lib/sinlist.h"
void delsame(sinlist<int> &sin);
int main()
{
    sinlist<int> sin;
    int n = 0;
    int temp = 0;
    cout<<"input val number n"<<endl;
    cin >> n;
    while (n--)
    {
        cin >> temp;
        sin.push_back(temp);
    }
    sin.print();
    delsame(sin);
    sin.print();
    return 0;
}
//与顺序表删除相同元素代码相同
void delsame(sinlist<int> &sin)
{
    for (int i = 1; i <= sin.size(); ++i)
    {
        int temp = sin.getval(i);
        bool flag = true;
        int pos = i + 1;
        while (flag)
        {
            int t = sin.findval(pos, temp);
            if (t != -1)
            {
                pos = t;
                sin.del(t);
            }
            if (t == -1)
                flag = false;
        }
    }
}