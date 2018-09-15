#include"message.h"

int message::_next_id = 0;

message::message(int cnc_num, int cnc_type, demand cnc_demand) :
    cnc_num(cnc_num), cnc_type(cnc_type), cnc_demand(cnc_demand)
{
    _message_id = _next_id++;
}

int message::get_id() const
{
    return _message_id;
}

bool message::operator==(const message & a) const
{
    return _message_id == a._message_id;
}

bool message::operator!=(const message & a) const
{
    return !(*this == a);
}
