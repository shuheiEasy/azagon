#include <timeSystem/timeSystem.hpp>

using namespace dataObject;
using namespace timeSystem;

Datetime::Datetime()
{
    _formatter.setFormat("${year}-${month}-${day} ${hour}:${min}:${sec} ${msec}");
    now();
}

Datetime::Datetime(int year, int month, int day, int hour, int min, int sec, int msec)
{
    _formatter.setFormat("${year}-${month}-${day} ${hour}:${min}:${sec} ${msec}");
    _converter(year, month, day, hour, min, sec, msec);
    _generateText();
}

Datetime::~Datetime() {}

const char *Datetime::getType() const { return "Datetime"; }

int Datetime::getSize() const { return 1; }

const char *Datetime::getLog() const { return _print_text.getChar(); }

void Datetime::now()
{
    _time.now();

    _year = 1970;
    _month = 1;
    _day = 1;

    auto timezone = getTimeZone();
    _time += timezone;
    _day2Calendar(_time.day());
    _hour = _time.hour();
    _minute = _time.minute();
    _second = _time.second();
    _millisec = _time.millisec();

    _generateText();
}

void Datetime::setFormat(const char *format)
{
    _formatter.setFormat(format);
    _generateText();
}
void Datetime::setFormat(const String &format)
{
    _formatter.setFormat(format);
    _generateText();
}

Int Datetime::year() const { return Int(_year); }
Int Datetime::year(const Int &year)
{
    _converter(year, _month, _day, _hour, _minute, _second, _millisec);
    _generateText();
    return Int(_year);
}
Int Datetime::month() const { return Int(_month); }
Int Datetime::month(const Int &month)
{
    _converter(_year, month, _day, _hour, _minute, _second, _millisec);
    _generateText();
    return Int(_month);
}
Int Datetime::day() const { return Int(_day); }
Int Datetime::day(const Int &day)
{
    _converter(_year, _month, day, _hour, _minute, _second, _millisec);
    _generateText();
    return Int(_day);
}
Int Datetime::hour() const { return Int(_hour); }
Int Datetime::hour(const Int &hour)
{
    _converter(_year, _month, _day, hour, _minute, _second, _millisec);
    _generateText();
    return Int(_hour);
}
Int Datetime::minute() const { return Int(_minute); }
Int Datetime::minute(const Int &minute)
{
    _converter(_year, _month, _day, _hour, minute, _second, _millisec);
    _generateText();
    return Int(_minute);
}
Int Datetime::second() const { return Int(_second); }
Int Datetime::second(const Int &second)
{
    _converter(_year, _month, _day, _hour, _minute, second, _millisec);
    _generateText();
    return Int(_second);
}
Int Datetime::millisec() const { return Int(_millisec); }
Int Datetime::millisec(const Int &millisec)
{
    _converter(_year, _month, _day, _hour, _minute, _second, millisec);
    _generateText();
    return Int(_millisec);
}

//////////////////////////////////
//
// private
//
//////////////////////////////////
void Datetime::_converter(int year, int month, int day, int hour, int min, int sec, int msec)
{

    if (year < MINYEAR || MAXYEAR < year)
    {
        printf("ERROR! 「year」の値が不正です。\n");
        exit(1);
    }
    _year = year;

    if (month < 1)
    {
        _month = 12 + (month % 12);
        _year += (month / 12);
        _year--;
    }
    else if (month > 12)
    {
        _month = month % 12;
        if (_month == 0)
        {
            _month = 12;
            _year--;
        }
        _year += (month / 12);
    }
    else
    {
        _month = month;
    }

    _day = 0;
    _time = Time(day, hour, min, sec, msec);
    _day2Calendar(_time.day());
    _hour = _time.hour();
    _minute = _time.minute();
    _second = _time.second();
    _millisec = _time.millisec();
}

void Datetime::_day2Calendar(int duration)
{
    if (duration > 0)
    {
        _day++;
        int remain_days = duration - 1;
        bool next_month_flag = false;

        switch (_month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
            if (_day > 31)
            {
                next_month_flag = true;
            }
            break;
        case 2:
            if (_year % 4 == 0)
            {
                if (_day > 29)
                {
                    next_month_flag = true;
                }
            }
            else
            {
                if (_day > 28)
                {
                    next_month_flag = true;
                }
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (_day > 30)
            {
                next_month_flag = true;
            }
            break;
        case 12:
            if (_day > 31)
            {
                _month = 1;
                _day = 1;
                _year++;
            }
            break;
        }

        // 次の月へ
        if (next_month_flag)
        {
            _day = 1;
            _month++;
        }

        // 経過日数が残っているならば
        if (remain_days > 0)
        {
            _day2Calendar(remain_days);
        }
    }
    else if (duration < 0)
    {
        _day--;
        int remain_days = duration + 1;
        bool next_month_flag = false;

        if (_day < 1)
        {
            _month--;
            switch (_month)
            {
            case 0:
                _year--;
                _month = 12;
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
                _day = 31;
                break;
            case 2:
                if (_year % 4 == 0)
                {
                    _day = 29;
                }
                else
                {
                    _day = 28;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                _day = 30;
                break;
            }
        }

        // 経過日数が残っているならば
        if (remain_days < 0)
        {
            _day2Calendar(remain_days);
        }
    }
}

void Datetime::_generateText()
{
    _formatter.setData("year", toString(_year));
    _formatter.setData("month", toString(_month));
    _formatter.setData("day", toString(_day));
    _formatter.setData("hour", toString(_hour));
    _formatter.setData("min", toString(_minute));
    _formatter.setData("sec", toString(_second));
    _formatter.setData("msec", toString(_millisec));

    _print_text = _formatter.generateText();
}
