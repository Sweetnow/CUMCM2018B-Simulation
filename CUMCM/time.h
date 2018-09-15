#ifndef TIME_H
#define TIME_H
const int MAX_SECOND = 60;
const int MAX_MINUTE = 60;
class time
{
private:
    int _second;
    int _minute;
    int _hour;
public:
    time(int second=0,int minute=0,int hour=0);
    ~time();
    int get_hour() const;
    int get_minute() const;
    int get_second() const;
    int convert_into_second() const;
    time operator+(const time &a)const;
    bool operator==(const time &a)const;
    bool operator!=(const time &a)const;
    bool operator<(const time &a)const;
    bool operator<=(const time &a)const;
    bool operator>=(const time &a)const;
    bool operator>(const time &a)const;
    time &operator++();
    time operator++(int);
};


#endif