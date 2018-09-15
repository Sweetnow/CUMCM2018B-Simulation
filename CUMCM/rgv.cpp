#include "rgv.h"


rgv::state rgv::get_state() const
{
    return _state;
}

void rgv::update(cnc cnc_array[CNC_NUM])
{
    switch (_state)
    {
    case rgv::MOVEING:
        if (*_pclock >= _stop)
        {
            _state = WAITING;
        }
        break;
    case rgv::WAITING:
        break;
    case rgv::LOADING:
        if (*_pclock >= _stop)
        {
            _state = WAITING;
        }
        break;
    case rgv::UNLOADING:
        if (*_pclock >= _stop)
        {
            if (_material.get_state() == material::RIPE)
            {
                _state = WASHING;
                _stop = *_pclock + RGV_WASH_TIME;
            }
            else
            {
                _state = WAITING;
            }
        }
        break;
    case rgv::WASHING:
        if (*_pclock >= _stop)
        {
            _state = WAITING;
        }
        break;
    default:
        break;
    }
    //according to msg, decide next state here
    //
    //
    //
    //
    //
    //       coding here
    //
    //
    //
    //
    //
}

material rgv::load(int cnc_num)
{
    _stop = *_pclock + CNC_EVENT_TIME[cnc_num % 2 == 1 ? ODD_LOAD : EVEN_LOAD];
    return _material;
}

void rgv::unload(material m, int cnc_num)
{
    _state = UNLOADING;
    _material = m;
    _stop = *_pclock + CNC_EVENT_TIME[cnc_num % 2 == 1 ? ODD_UNLOAD : EVEN_UNLOAD];
}

void rgv::move(int pos)
{
    int dst = abs(pos - _pos);
    if (dst == 0)
    {
        _state = WAITING;
    }
    else if (dst >= 1 && dst <= 3)
    {
        _stop = *_pclock + RGV_MOVE_TIME[dst];
        _state = MOVEING;
    }
}

rgv::rgv(time * pclock, std::vector<message> *pmsg) :
    _pclock(pclock), _pmsg(pmsg)
{
}

rgv::~rgv()
{
}
