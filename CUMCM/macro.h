#ifndef MACRO_H
#define MACRO_H
#include"time.h"

#define MULTIPLE    //situation 2 two process

enum cnc_event
{
    ONE_PROCESS,            //one process
    FIRST_OF_PROCESSES,     //first of the two processes
    SECOND_OF_PROCESSES,    //second
    ODD_LOAD,               //CNC1# 3# 5# 7# loading
    ODD_UNLOAD,             //CNC1# 3# 5# 7# unloading
    EVEN_LOAD,              //CNC2# 4# 6# 8# loading
    EVEN_UNLOAD,            //CNC1# 3# 5# 7# unloading
    CNC_EVENT_NUM
};
const time CNC_EVENT_TIME[CNC_EVENT_NUM] = { 560,400,378,28,28,31,31 };   //second

const unsigned int CNC_NUM = 8;
//time that RGV's moving uses.  0  1  2 3
const time RGV_MOVE_TIME[4] = { 0,20,33,46 };   //second
const time RGV_WASH_TIME = 25;
const time MAX_TIME(0, 0, 8);
const time CNC_BROKEN_MIN(0, 10, 0);
const time CNC_BROKEN_MAX(0, 20, 0);

#endif