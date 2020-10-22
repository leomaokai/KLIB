#include "lib/seqlist.h"
#include "lib/sincirlist.h"
void josephus1(seqlist<int> &seq, int s, int m);
void josephus2(sincirlist<int> &mlist, int s, int m);
int main()
{
    seqlist<int> seq;
    int n = 0;
    cout << "input n:" << endl;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        seq.push_back(i);
    seq.print();
    josephus1(seq, 1, 4);
    sincirlist<int> mlist;
    for (int i = 1; i <= n; ++i)
        mlist.push_back(i);
    mlist.print();
    josephus2(mlist, 1, 4);
    return 0;
}
//顺序表实现约瑟夫环,下标从0开始
void josephus1(seqlist<int> &seq, int s, int m)
{
    int count = seq.num();
    s -= 1;
    m -= 1;
    while (count--)
    {
        int size = seq.num();
        s = (s + m) % size;
        cout << seq.getval(s) << " ";
        seq.del(s);
    }
    cout << endl;
}
//循环链表实现约瑟夫,下标从1开始
void josephus2(sincirlist<int> &mlist, int s, int m)
{
    int count = mlist.size();
    m -= 1;
    while (count--)
    {
        int size = mlist.size();
        if ((s = (s + m) % size) == 0)
            s = size;
        cout << mlist.getval(s) << " ";
        mlist.del(s);
    }
}