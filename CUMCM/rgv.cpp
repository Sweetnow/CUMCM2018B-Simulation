#include "rgv.h"


int rgv::get_ripe_count() const
{
    return _ripe;
}

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
            ++_ripe;
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
    if (_state == WAITING && _pmsg->size() > 0)
    {
        std::vector<msg_dst_pair> msg_with_dst;
        msg_with_dst.reserve(_pmsg->size());
        message *pnext_demand = nullptr;
        for (const auto &one : *_pmsg)
        {
            msg_with_dst.push_back(std::make_pair(abs(get_pos(one.cnc_num) - _pos), one));
        }
        //sort by priority: demand_type(perfer loading) > distance > number of cnc(perfer odd number)
        std::sort(msg_with_dst.begin(), msg_with_dst.end(), rgv::compare);
        pnext_demand = &msg_with_dst.front().second;

        if (get_distance(*pnext_demand) == 0)
        {
            switch (pnext_demand->cnc_demand)
            {
            case message::WAIT_LOADING:
                //just for condition 1
                _material = material(true);
                cnc_array[pnext_demand->cnc_num - 1].load(load(pnext_demand->cnc_num));
                _pmsg->erase(std::find(_pmsg->begin(), _pmsg->end(), *pnext_demand));
                break;
            case message::WAIT_UNLOADING:
                unload(cnc_array[pnext_demand->cnc_num - 1].unload(), pnext_demand->cnc_num);
                _pmsg->erase(std::find(_pmsg->begin(), _pmsg->end(), *pnext_demand));
                break;
            default:
                break;
            }
        }
        else if (get_distance(*pnext_demand) > 0)
        {
            move(get_pos(pnext_demand->cnc_num));
        }
    }
}

material rgv::load(int cnc_num)
{
    _state = LOADING;
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
    _pos = pos;
}

rgv::rgv(time * pclock, std::vector<message> *pmsg) :
    _pclock(pclock), _pmsg(pmsg)
{
}

rgv::~rgv()
{
}

bool rgv::compare(const msg_dst_pair & a, const msg_dst_pair & b)
{
    //priority: demand_type(perfer loading) > distance > number of cnc(perfer odd number)
    return a.second.cnc_demand < b.second.cnc_demand || (a.second.cnc_demand == b.second.cnc_demand && a.first < b.first)
        || (a.second.cnc_demand == b.second.cnc_demand && a.first == b.first && a.second.cnc_num < b.second.cnc_num);

    //priority:  distance > number of cnc(perfer odd number)
    /*return (a.first < b.first)
        || (a.first == b.first && a.second.cnc_num < b.second.cnc_num);*/
}

int rgv::get_distance(const message &msg) const
{
    return abs(get_pos(msg.cnc_num) - _pos);
}
