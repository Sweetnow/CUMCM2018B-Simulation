#include<iostream>
#include<fstream>
#include<vector>
#include"time.h"
#include"macro.h"
#include"cnc.h"
#include"rgv.h"

using std::vector;
using std::cout;
using std::endl;
using std::cin;

vector<message> msg;
time clock(0, 0, 0);
rgv r(&clock, &msg);
#ifdef MULTIPLE
cnc cnc_array[CNC_NUM] =
{
    {1,1,&clock,&msg},
    {2,2,&clock,&msg},
    {3,1,&clock,&msg},
    {4,2,&clock,&msg},
    {5,1,&clock,&msg},
    {6,2,&clock,&msg},
    {7,1,&clock,&msg},
    {8,2,&clock,&msg},
};
#else
cnc cnc_array[CNC_NUM] =
{
    {1,0,&clock,&msg},
    {2,0,&clock,&msg},
    {3,0,&clock,&msg},
    {4,0,&clock,&msg},
    {5,0,&clock,&msg},
    {6,0,&clock,&msg},
    {7,0,&clock,&msg},
    {8,0,&clock,&msg},
};
#endif // MULTIPLE

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
    cout << "8小时完成熟料数量：" << r.get_ripe_count() << endl;
    std::ofstream log_file("log.csv");
    if (log_file.is_open())
    {
        r.output_log(log_file);
    }
    else
    {
        cout << "cannot open file!" << endl;
    }
    cin.get();
    return 0;
}