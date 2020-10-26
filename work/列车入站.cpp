#include <iostream>
using namespace std;
void solution(const int &n)
{
    int *t = new int[n + 1]();
    t[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (!t[i])
        {
            for (int j = 0; j <= i - 1; j++)
                t[i] += t[j] * t[i - 1 - j];
        }
    }
    cout << t[n] << endl;
    delete[] t;
}
int main()
{
    int n = 0;
    cin >> n;
    solution(n);
    return 0;
}
