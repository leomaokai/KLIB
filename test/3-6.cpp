#include"../lib/head.h"
/*
匕首代号A,雷鸣刀代号B,穿云弓代号C,冲击之枪代号D,冲能拳套代号E,破晓代号F
*/
class equipment
{
    public:
    equipment():price(0),ability(0)
    {}
    ~equipment()
    {}
    int price;
    int ability;
    equipment *lchild;
    equipment *brother;
    equipment *father;
};
