#include<iostream>
#include<vector>
#include"time.h"
#include"macro.h"
#include"cnc.h"
#include"rgv.h"
using std::vector;

vector<message> msg;
time clock(0, 0, 0);
rgv r(&clock, &msg);
cnc cnc_array[CNC_NUM] = { cnc(1,&clock,&msg),cnc(2,&clock,&msg),cnc(3,&clock,&msg),cnc(4,&clock,&msg),
                            cnc(5,&clock,&msg),cnc(6,&clock,&msg),cnc(7,&clock,&msg),cnc(8,&clock,&msg), };

int main()
{
    while (clock < MAX_TIME)
    {
        for (size_t i = 0; i < CNC_NUM; i++)
        {
            cnc_array[i].update();
        }
        //1% break down one cnc????
        r.update(cnc_array);
        ++clock;
    }
    return 0;
}