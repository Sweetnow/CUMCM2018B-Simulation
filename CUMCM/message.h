#ifndef MESSAGE_H
#define MESSAGE_H

class message
{
public:
    enum demand { WAIT_LOADING, WAIT_UNLOADING };
    int cnc_num;
    int cnc_type;
    demand cnc_demand;
    message(int cnc_num, int cnc_type, demand cnc_demand);
    int get_id() const;
    bool operator==(const message &a) const;
    bool operator!=(const message &a) const;
private:
    static int _next_id;
    int _message_id;
};

#endif // !MESSAGE_H