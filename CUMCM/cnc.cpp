#include "cnc.h"



cnc::state cnc::get_state() const
{
    return _state;
}

int cnc::get_num() const
{
    return _num;
}

void cnc::update()
{
    switch (_state)
    {
    case cnc::WORKING:
        if (*_pclock >= _stop)
        {
            _state = WAITING_UNLOAD;
            //report
            _pmsg->push_back({ _num, message::WAIT_UNLOADING });
        }
        break;
    case cnc::WAITING_LOAD:
        break;
    case cnc::WAITING_UNLOAD:
        break;
    case cnc::LOADING:
        if (*_pclock >= _stop)
        {
            //start working
            _state = WORKING;
            time work = (_material.is_one() ? CNC_EVENT_TIME[ONE_PROCESS] :
                (_material.get_state() == material::HALF ?
                    CNC_EVENT_TIME[SECOND_OF_PROCESSES] : CNC_EVENT_TIME[FIRST_OF_PROCESSES]));
            _stop = work + *_pclock;
        }
        break;
    case cnc::UNLOADING:
        if (*_pclock >= _stop)
        {
            _state = WAITING_LOAD;
            //report
            _pmsg->push_back({ _num, message::WAIT_LOADING });
        }
        break;
    case cnc::BROKEN:
        if (*_pclock >= _stop)
        {
            _state = WAITING_LOAD;
            _pmsg->push_back({ _num, message::WAIT_LOADING });
            //report
        }
        break;
    default:
        break;
    }
}

void cnc::load(material m)
{
    _material = m;
    _state = LOADING;
    _stop = *_pclock + CNC_EVENT_TIME[_num % 2 == 1 ? ODD_LOAD : EVEN_LOAD];
}

void cnc::break_down()
{
    _state = BROKEN;
    _material.set_state(material::BAD);
    time broken = rand() / (CNC_BROKEN_MAX.convert_into_second() - CNC_BROKEN_MIN.convert_into_second())
        + CNC_BROKEN_MIN.convert_into_second();
    _stop = broken + *_pclock;
}


material cnc::unload()
{
    _state = UNLOADING;
    switch (_material.get_state())
    {
    case material::RAW:
        if (_material.is_one())
            _material.set_state(material::RIPE);
        else
            _material.set_state(material::HALF);
        break;
    case material::HALF:
        _material.set_state(material::RIPE);
        break;
    default:
        break;
    }
    _stop = *_pclock + CNC_EVENT_TIME[_num % 2 == 1 ? ODD_UNLOAD : EVEN_UNLOAD];
    return _material;
}

cnc::cnc(int num, time *clock, std::vector<message> *pmsg) :
    _pclock(clock), _pmsg(pmsg), _num(num)
{
}


cnc::~cnc()
{
}

