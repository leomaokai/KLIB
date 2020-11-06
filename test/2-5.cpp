/*
拓展题：智能交通管理是人工智能应用的一个重要方向，在使用智能算法解决交通问题前，需要给相应的问题进行建模。本题请运用队列为某十字路口车辆积压情况进行简单建模。
初始条件（最好使用多线程编程）：
	路口交通灯为红绿圆灯（黄灯3秒按绿灯3秒计算），每60秒交替； //绿灯63秒,红灯60秒
	初始路口各方向有3辆车；
	设路口每个方向进入的车辆随机9~15辆/分钟；
	设每辆车通过路口的时间随机4~5秒/辆
*/
//visual studio 2019 
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
    void transform()
    {
        while (true)
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
        srand(time(0));
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 4));
            east.push(1);
        }
    }
    void pushcarwest()
    {
        srand(time(0));
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 4));
            west.push(1);
        }
    }
    void pushcarsouth()
    {
        srand(time(0));
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 4));
            south.push(1);
        }
    }
    void pushcarnorth()
    {
        srand(time(0));
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 4));
            north.push(1);
        }
    }
    void passeast()
    {
        srand(time(0));
        while (true)
        {
            if (traffic.getlight1())//检测是否为绿灯
            {
                while (!east.empty())//如果路口堵有车辆
                {
                    east.pop();//车辆通过路口
                    ++count1;//计数+1
                    //cout << "east to west pass " << count1 << " cars" << endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(rand() % 2 + 4));//车辆通过路口时间4~5秒
            }
            //std::this_thread::sleep_for(std::chrono::seconds(1));//一秒后再次检测红绿灯
        }
    }
    void passwest()
    {
        srand(time(0));
        while (true)
        {
            if (traffic.getlight1())
            {
                while (!west.empty())
                {
                    west.pop();
                    ++count2;
                    //cout << "west to east pass " << count2 << " cars" << endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(rand() % 2 + 4));
            }
            //std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    void passsouth()
    {
        srand(time(0));
        while (true)
        {
            if (traffic.getlight2())
            {
                while (!south.empty())
                {
                    south.pop();
                    ++count3;
                    //cout << "south to north pass " << count3 << " cars" << endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(rand() % 2 + 4));
            }
            //std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    void passnorh()
    {
        srand(time(0));
        while (true)
        {
            if (traffic.getlight2())
            {
                while (!north.empty())
                {
                    north.pop();
                    ++count4;
                    //cout << "north to south pass " << count4 << " cars" << endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(rand() % 2 + 4));
            }
            //std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    int total()
    {
        return count1 + count2 + count3 + count4;
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
    int time = 0;
    cout << "input time" << endl;
    cin >> time;
    thread threadlamp(&lamp::transform, &traffic);//交通灯60秒替换
    threadlamp.detach();//线程分离
    crossroad p1;
    thread threadpushcareast1(&crossroad::pushcareast, &p1);//东路口随机进车
    thread threadpushcarwest1(&crossroad::pushcarwest, &p1);//西路口随机进车
    thread threadpushcarsouth1(&crossroad::pushcarsouth, &p1);//南路口随机进车
    thread threadpushcarnorth1(&crossroad::pushcarnorth, &p1);//西路口随机进车
    thread threadeast1(&crossroad::passeast, &p1);//东西通过
    thread threadwest1(&crossroad::passwest, &p1);//西东通过
    thread threadsouth1(&crossroad::passsouth, &p1);//南北通过
    thread threadnorth1(&crossroad::passnorh, &p1);//北南通过
    threadpushcareast1.detach();
    threadpushcarwest1.detach();
    threadpushcarsouth1.detach();
    threadpushcarnorth1.detach();
    threadeast1.detach();
    threadwest1.detach();
    threadsouth1.detach();
    threadnorth1.detach();
    for (int i = time; i > 0; --i)
    {
        cout << i << " ";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << endl;
    cout << "test : all cars " << p1.total() << endl;

    return 0;
}