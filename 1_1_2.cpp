#include "lib/seqlist.h"
void delsame(seqlist<int> &seq); //删除相同元素
void part(seqlist<int> &seq);    //将元素以0为基准分成两个顺序表
int main()
{
    seqlist<int> seq;
    int temp = 0;
    int n = 0;
    cout << "input val number :" << endl;
    cin >> n;
    while (n--)
    {
        cin >> temp;
        seq.push_back(temp);
    }
    seq.print();
    cout << "delete the same val" << endl;
    delsame(seq);
    seq.print();
    cout << "tow part >0 and <0" << endl;
    part(seq);
    return 0;
}
void delsame(seqlist<int> &seq)
{
    for (int i = 0; i < seq.num(); ++i)
    {
        int temp = seq.getval(i); //得到第i个位置的元素
        int pos = i + 1;          //刚开始从i+1位置开始查找
        bool flag = true;
        while (flag)
        {
            int t = seq.findval(pos, temp); //从pos位置开始查找
            if (t != -1)                    //如果找到则删除
            {
                pos = t;    //为删除位置,下次从删除位置开始查找
                seq.del(t); //删除第t位置的元素
            }
            else //没有相同的元素
                flag = false;
        }
    }
}
void part(seqlist<int> &seq)
{
    seqlist<int> temp1;
    seqlist<int> temp2;
    for (int i = 0; i < seq.num(); ++i)
    {
        if (seq.getval(i) > 0)
            temp1.push_back(seq.getval(i));
        else
            temp2.push_back(seq.getval(i));
    }
    temp1.print();
    temp2.print();
}