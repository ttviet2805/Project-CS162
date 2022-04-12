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
