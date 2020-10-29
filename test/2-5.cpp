/*
拓展题：智能交通管理是人工智能应用的一个重要方向，在使用智能算法解决交通问题前，需要给相应的问题进行建模。本题请运用队列为某十字路口车辆积压情况进行简单建模。
初始条件（最好使用多线程编程）：
	路口交通灯为红绿圆灯（黄灯3秒按绿灯3秒计算），每60秒交替； //绿灯63秒,红灯60秒
	初始路口各方向有3辆车；
	设路口每个方向进入的车辆随机9~15辆/分钟；
	设每辆车通过路口的时间随机4~5秒/辆
*/
#include "../lib/queue.h"
srand(time(0));
template <typename T>
class crossroad
{
public:
    crossroad();
    ~crossroad();

private:
    Queue<int> east;  //东路口
    Queue<int> west;  //西路口
    Queue<int> south; //南路口
    Queue<int> north; //北路口
    bool red;         //红灯
    bool green;       //绿灯
};
int main()
{
}
crossroad<T>::crossroad() : red(60), green(63)
{
    for (int i = 0; i < 3; ++i) // 1 代表有车,入队3个1代表有3辆车
    {
        east.push(1);
        west.push(1);
        south.push(1);
        north.push(1);
    }
}
crossroad<T>::~crossroad()
{
}