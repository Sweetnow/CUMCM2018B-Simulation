#ifndef MESSAGE_H
#define MESSAGE_H


class message
{
public:
    enum demand { WAIT_LOADING, WAIT_UNLOADING };
    int cnc_num;
    demand cnc_demand;
    static int _next_id;
    message(int cnc_num, demand cnc_demand);
    bool operator==(const message &a);
    bool operator!=(const message &a);
private:
    int _message_id;
};

#endif // !MESSAGE_H