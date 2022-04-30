#include "DateHeader.h"

void Date::OutputDate()
{
    cout << Day << " " << Month << " " << Year << '\n';
}

void Date::InputDate()
{
    cout << "(DD MM YYYY) ";
    cin >> Day >> Month >> Year;
}

void Date::changeDate(int D, int M, int Y)
{
    Day = D, Month = M, Year = Y;
}

int daysInMonth(int month, int year){
    switch (month){
        case 1: return 31;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
                return 29;
            else
                return 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
}
bool isValidDate(Date date){
    int day = date.Day;
    int month = date.Month;
    int year = date.Year;
    if (year < 1)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day > 0 && day <= daysInMonth(month, year))
        return true;
    return false;
}
