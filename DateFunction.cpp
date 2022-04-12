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

void Date::changeDate(int _Day, int _Month, int _Year) {
    Day = _Day, Month = _Month, Year = _Year;
}
