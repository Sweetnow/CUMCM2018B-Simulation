#include"message.h"

int message::_next_id = 0;

message::message(int cnc_num, demand cnc_demand) :
    cnc_num(cnc_num), cnc_demand(cnc_demand)
{
    _message_id = _next_id++;
}

bool message::operator==(const message & a)
{
    return _message_id == a._message_id;
}

bool message::operator!=(const message & a)
{
    return !(*this == a);
}
