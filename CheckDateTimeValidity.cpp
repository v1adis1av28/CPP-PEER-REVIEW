const int MIN_YEAR = 1;
const int MAX_YEAR = 9999;
const int MAX_HOURS_DAY = 23;
const int MAX_MONTH_COUNT = 12;
const int MIN_MONTH_COUNT = 1;
const int MAX_SECONDS_MINUTE_IN = 60;

void CheckYearValidity(int year)
{
    if (year < MIN_YEAR) {
        throw domain_error("year is too small"s);
    }
    if (year > MAX_YEAR)
    {
        throw domain_error("year is too big"s);
    }
}

void CheckMonthValidity(int month)
{
    if (month < MIN_MONTH_COUNT)
    {
        throw domain_error("month is too small"s);
    }
    if (month > MAX_MONTH_COUNT)
    {
        throw domain_error("month is too big"s);
    }
}

void CheckDayValidity(int day, int month, int year)
{
    const bool is_leap_year = (year % 4 == 0) && !(year % 100 == 0 && year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (day < 1)
    {
        throw domain_error("day is too small"s);
    }
    if (day > month_lengths[month - 1])
    {
        throw domain_error("day is too big"s);
    }
}

void CheckHourValidity(int hour)
{
    if (hour < 0)
    {
        throw domain_error("hour is too small"s);
    }
    if (hour > MAX_HOURS_DAY)
    {
        throw domain_error("hour is too big"s);
    }
}

void CheckMinuteValidity(int minute)
{
    if (minute < 0)
    {
        throw domain_error("minute is too small"s);
    }
    if (minute > MAX_SECONDS_MINUTE_IN)
    {
        throw domain_error("minute is too big"s);
    }
}

void CheckSecondValidity(int second)
{
    if (second < 0) 
    {
        throw domain_error("second is too small");
    }
    if (second > MAX_SECONDS_MINUTE_IN)
    {
        throw domain_error("second is too big"s);
    }
}


void CheckDateTimeValidity(const DateTime& dt)
{
    CheckYearValidity(dt.year);
    CheckMonthValidity(dt.month);
    CheckDayValidity(dt.day, dt.month, dt.year);
    CheckHourValidity(dt.hour);
    CheckMinuteValidity(dt.minute);
    CheckSecondValidity(dt.second);
}