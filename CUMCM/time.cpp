#include "time.h"



time::time(int second, int minute, int hour) :
    _second(second), _minute(minute), _hour(hour)
{
    _minute += _second / MAX_SECOND;
    _second %= MAX_SECOND;
    _hour += _minute / MAX_MINUTE;
    _minute %= MAX_MINUTE;
}


time::~time()
{
}

int time::get_hour() const
{
    return _hour;
}

int time::get_minute() const
{
    return _minute;
}

int time::get_second() const
{
    return _second;
}

int time::convert_into_second() const
{
    return (_hour * MAX_MINUTE + _minute) * MAX_SECOND + _second;
}

time time::operator+(const time & a)const
{
    time tmp = *this;
    tmp._hour += a._hour;
    tmp._minute += a._minute;
    tmp._second += a._second;
    //carry-over
    tmp._minute += tmp._second / MAX_SECOND;
    tmp._second %= MAX_SECOND;
    tmp._hour += tmp._minute / MAX_MINUTE;
    tmp._minute %= MAX_MINUTE;
    return tmp;
}

bool time::operator==(const time & a) const
{
    return _hour == a._hour&&_minute == a._minute&&_second == a._second;
}

bool time::operator!=(const time & a) const
{
    return !(*this == a);
}

bool time::operator<(const time & a) const
{
    return this->convert_into_second() < a.convert_into_second();
}

bool time::operator<=(const time & a) const
{
    return this->convert_into_second() <= a.convert_into_second();
}

bool time::operator>=(const time & a) const
{
    return this->convert_into_second() >= a.convert_into_second();
}

bool time::operator>(const time & a) const
{
    return this->convert_into_second() > a.convert_into_second();
}

time & time::operator++()
{
    *this = *this + time(1);
    return *this;
}

time time::operator++(int)
{
    time tmp(*this);
    *this = *this + time(1);
    return tmp;
}
