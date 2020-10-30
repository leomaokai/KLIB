/*
拓展题：智能交通管理是人工智能应用的一个重要方向，在使用智能算法解决交通问题前，需要给相应的问题进行建模。本题请运用队列为某十字路口车辆积压情况进行简单建模。
初始条件（最好使用多线程编程）：
	路口交通灯为红绿圆灯（黄灯3秒按绿灯3秒计算），每60秒交替； //绿灯63秒,红灯60秒
	初始路口各方向有3辆车；
	设路口每个方向进入的车辆随机9~15辆/分钟；
	设每辆车通过路口的时间随机4~5秒/辆
*/
// vasual studio 2019编译
#include <thread>
#include <time.h>
#include <queue>
#include <mutex>
#include <iostream>
using namespace std;
mutex m;
class lamp
{
public:
    lamp() : light1(true), light2(false) //初始东西绿灯
    {
    }
    void transform(int m)
    {
        while (m--)
        {
            std::this_thread::sleep_for(std::chrono::seconds(60));//60秒替换
            light1 = !light1;
            light2 = !light2;
        }
    }
    bool getlight1() { return light1; }
    bool getlight2() { return light2; }
private:
    //两个灯,且状态相反,1控制东西,2控制南北
    bool light1; //true 为绿灯, flase 为红灯
    bool light2;
};
lamp traffic;
class crossroad
{
public:
    crossroad() : count1(0),count2(0),count3(0),count4(0)
    {
        for (int i = 0; i < 3; ++i)//初始每个路口三辆车,1代表车,队列中3个1代表3辆车
        {
            east.push(1);
            west.push(1);
            south.push(1);
            north.push(1);
        }
    }
    //4~6秒每个方向进一辆车
    void pushcareast()
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 4));
            east.push(1);
        }
    }
    void pushcarwest()
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 4));
            west.push(1);
        }
    }
    void pushcarsouth()
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 4));
            south.push(1);
        }
    }
    void pushcarnorth()
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 4));
            north.push(1);
        }
    }
    void passeast(int n)
    {
        while (n--)
        {
            while (traffic.getlight1())
            {
                while (!east.empty())
                {
                    east.pop();
                    ++count1;
                    cout << "east to west pass " << count1 << " cars" << endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(rand() % 2 + 4));
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    void passwest(int n)
    {
        while (n--)
        {
            while (traffic.getlight1())
            {
                while (!west.empty())
                {
                    west.pop();
                    ++count2;
                    cout << "west to east pass " << count2 << " cars" << endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(rand() % 2 + 4));
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    void passsouth(int n)
    {
        while (n--)
        {
            while (traffic.getlight2())
            {
                while (!south.empty())
                {
                    south.pop();
                    ++count3;
                    cout << "south to north pass " << count3 << " cars" << endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(rand() % 2 + 4));
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    void passnorh(int n)
    {
        while (n--)
        {
            while (traffic.getlight2())
            {
                while (!north.empty())
                {
                    north.pop();
                    ++count4;
                    cout << "north to south pass " << count4 << " cars" << endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(rand() % 2 + 4));
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    ~crossroad() {}

private:
    queue<int> east;  //东路口
    queue<int> west;  //西路口
    queue<int> south; //南路口
    queue<int> north; //北路口
    int count1,count2,count3,count4;
};
int main()
{
    crossroad p;
    int n = 240;
    thread threadlamp(&lamp::transform,&traffic,4);
    thread threadcar1(&crossroad::pushcareast, &p);
    thread threadcar2(&crossroad::pushcarwest, &p);
    thread threadcar3(&crossroad::pushcarsouth, &p);
    thread threadcar4(&crossroad::pushcarnorth, &p);
    thread threadeast(&crossroad::passeast, &p,n);
    thread threadwest(&crossroad::passwest, &p,n);
    thread threadsouth(&crossroad::passsouth, &p,n);
    thread threadnorth(&crossroad::passnorh, &p,n);
    threadlamp.join();
    threadcar1.join();
    threadcar2.join();
    threadcar3.join();
    threadcar4.join();
    threadeast.join();
    threadwest.join();
    threadsouth.join();
    threadnorth.join();

    return 0;
}