#ifndef MESSAGE_H
#define MESSAGE_H


struct message
{
    enum demand { WAIT_LOADING, WAIT_UNLOADING };
    int cnc_num;
    demand cnc_demand;
};

#endif // !MESSAGE_H