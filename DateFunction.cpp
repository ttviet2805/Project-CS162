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
