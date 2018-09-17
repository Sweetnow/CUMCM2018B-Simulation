#ifndef CNC_H
#define CNC_H

#include<cstdlib>
#include"macro.h"
#include"time.h"
#include"material.h"
#include"message.h"
#include<vector>

class cnc
{
public:
    enum state
    {
        WORKING,
        WAITING_LOAD,
        WAITING_UNLOAD,
        LOADING,
        UNLOADING,
        BROKEN
    };

    state get_state() const;
    int get_num() const;
    int get_type() const;
    void update();  //update cnc state per second

    // all control functions below assumes that 
    // all about it are legal such as cnc_state and the time that
    // material loads and unloads
    void load(material m);
    void break_down();
    material unload();
    cnc(int num, int type, time *pclock, std::vector<message> *pmsg);
    ~cnc();
private:
    state _state = WAITING_LOAD;
    material _material;
    time _stop;
    time *_pclock;   //global clock
    std::vector<message> *_pmsg;
    int _num;
    int _type;  //0-situation 1(only one process)
                //1-situation 2(first process)
                //2-situation 2(second process)
};

inline int get_pos(int num)
{
    return (num - 1) / 2;
}

#endif // !CNC_H
