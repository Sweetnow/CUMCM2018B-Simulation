#ifndef RGV_H
#define RGV_H

#include"time.h"
#include"material.h"
#include"macro.h"
#include<cmath>
#include<vector>
#include"message.h"
#include"cnc.h"

class rgv
{
public:
    enum state
    {
        MOVEING,
        WAITING,
        LOADING,
        UNLOADING,
        WASHING
    };

    state get_state() const;
    void update(cnc cnc_array[CNC_NUM]);
    //assume that RGV is located in the correct position
    material load(int cnc_num);
    void unload(material m, int cnc_num);
    void move(int pos);
    rgv(time *pclock, std::vector<message> *pmsg);
    ~rgv();

private:
    state _state = WAITING;
    //      CNC2#  CNC4#  CNC6#  CNC8#
    //_pos    0      1      2      3
    //      CNC1#  CNC3#  CNC5#  CNC7#
    int _pos = 0;
    material _material;
    time _stop;
    time *_pclock;
    std::vector<message> *_pmsg;
};

#endif // !RGV_H