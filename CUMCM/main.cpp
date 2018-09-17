#include<iostream>
#include<fstream>
#include<vector>
#include"time.h"
#include"macro.h"
#include"cnc.h"
#include"rgv.h"
#include<string>

#define GET_BIT(byte,n) (((byte)>>(n)) & 0x0001) 

using std::vector;
using std::cout;
using std::endl;
using std::cin;




int main()
{
    unsigned char best_code;
    int max_result = 0;
    for (unsigned short c = 81; c <= 81; ++c)
    {
        vector<message> msg;
        time clock(0, 0, 0);
#ifdef MULTIPLE
        cnc cnc_array[CNC_NUM] =
        {
            {1,GET_BIT(c,0) + 1,&clock,&msg},
            {2,GET_BIT(c,1) + 1,&clock,&msg},
            {3,GET_BIT(c,2) + 1,&clock,&msg},
            {4,GET_BIT(c,3) + 1,&clock,&msg},
            {5,GET_BIT(c,4) + 1,&clock,&msg},
            {6,GET_BIT(c,5) + 1,&clock,&msg},
            {7,GET_BIT(c,6) + 1,&clock,&msg},
            {8,GET_BIT(c,7) + 1,&clock,&msg},
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
        rgv r(&clock, &msg, cnc_array);
        while (clock < MAX_TIME)
        {
            for (size_t i = 0; i < CNC_NUM; i++)
            {
                cnc_array[i].update();
            }
            //1% break down one cnc????
            r.update();
            ++clock;
        }
        if (r.get_ripe_count() > max_result)
        {
            max_result = r.get_ripe_count();
            best_code = c;
        }
    }

    vector<message> msg;
    time clock(0, 0, 0);
#ifdef MULTIPLE
    cnc cnc_array[CNC_NUM] =
    {
        {1,GET_BIT(best_code,0) + 1,&clock,&msg},
        {2,GET_BIT(best_code,1) + 1,&clock,&msg},
        {3,GET_BIT(best_code,2) + 1,&clock,&msg},
        {4,GET_BIT(best_code,3) + 1,&clock,&msg},
        {5,GET_BIT(best_code,4) + 1,&clock,&msg},
        {6,GET_BIT(best_code,5) + 1,&clock,&msg},
        {7,GET_BIT(best_code,6) + 1,&clock,&msg},
        {8,GET_BIT(best_code,7) + 1,&clock,&msg},
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
    rgv r(&clock, &msg,cnc_array);
    while (clock < MAX_TIME)
    {
        for (size_t i = 0; i < CNC_NUM; i++)
        {
            cnc_array[i].update();
        }
        //1% break down one cnc????
        r.update();
        ++clock;
    }

    cout << "8小时完成熟料数量：" << r.get_ripe_count() << endl;
    std::string file_name = ".csv";
#ifdef MULTIPLE
    file_name = "_multiple" + file_name;
#endif // MULTIPLE
#ifdef BREAK_DOWN
    file_name = "_bad" + file_name;
#endif
    file_name = "situation_3" + file_name;
    std::ofstream log_file(file_name);
    if (log_file.is_open())
    {
        r.output_log(log_file);
        log_file.close();
    }
    else
    {
        cout << "cannot open file!" << endl;
    }
    cin.get();
    return 0;
}