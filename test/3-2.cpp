#include "../lib/head.h"

void solution1() //效率最高,类似于哈夫曼,概率高得更早判断
{
    int n = 0;
    while (1)
    {
        cout << "input score or -1 quit" << endl;
        cin >> n;
        if (n < 0 || n > 100)
        {
            return;
        }
        else
        {
            if (n >= 80 && n <= 89)
                cout << "grade is B" << endl;
            else
            {
                if(n>=70 && n<=79)
                    cout<<"grade is C"<<endl;
                else 
                {
                    if(n>=90 && n<=100)
                        cout<<"grade is A"<<endl;
                    else
                    {
                        if(n>=60 && n<=69)
                            cout<<"grade is D"<<endl;
                        else 
                            cout<<"grade is E"<<endl;
                    }
                }
            }
        }
        if (n == -1)
            return;
    }
}
void solution2() //层数最小,完全二叉树,将0-79 80-100分开
{
    int n = 0;
    while (1)
    {
        cout << "input score or -1 quit" << endl;
        cin >> n;
        if (n >= 0 && n <= 79)
        {
            if (n <= 69)
            {
                if (n > 59)
                    cout << "grade is D" << endl;
                else
                    cout << "grade is E" << endl;
            }
            else
                cout << "grade is C" << endl;
        }
        else if (n >= 80 && n <= 100)
        {
            if (n <= 89)
                cout << "grade is B" << endl;
            else
                cout << "grade is A" << endl;
        }
        if (n == -1)
            return;
    }
}
int main()
{
    solution1();
    solution2();
    return 0;
}