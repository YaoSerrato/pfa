#include "DateTime.hpp"

DateTime::DateTime()
{
}


DateTime::~DateTime()
{
}


void DateTime::GetFullDateTime(char (*data)[FULL_DATETIME_LENGTH])
{
    std::time_t result = std::time(nullptr);
 
    std::strncpy(*data, std::ctime(&result), FULL_DATETIME_LENGTH);
    assert('\n' == (*data)[std::strlen(*data) - 1]);
}


void DateTime::GetYearMonth(char (*data)[YEARMONTH_LENGTH])
{
    // Format -> "Sun Nov 03 19:37:05 2024\n" (25 characters)
    std::time_t result = std::time(nullptr);
    char full_date[FULL_DATETIME_LENGTH];
 
    std::strncpy(full_date, std::ctime(&result), FULL_DATETIME_LENGTH);
    std::strncpy(*data, &full_date[20], 4);             // copy year
    std::strncpy(&((*data)[4]), &full_date[4], 3);      // copy month
    (*data)[YEARMONTH_LENGTH - 1] = '\0';               // Ensure null-termination

    assert('\0' == (*data)[YEARMONTH_LENGTH - 1]);
}


std::string DateTime::GetMonthNumber(void)
{
    // surely this method can be optimized

    // Format -> "Sun Nov 03 19:37:05 2024\n" (25 characters)
    std::time_t result = std::time(nullptr);
    char temp_month[3] = {'\0'};
    char full_date[FULL_DATETIME_LENGTH];
    std::string ret;
 
    std::strncpy(full_date, std::ctime(&result), FULL_DATETIME_LENGTH);
    std::strncpy(temp_month, &full_date[4], 3);             // copy month

    if(('J' == temp_month[0]) && ('a' == temp_month[1]) && ('n' == temp_month[2])) //  {Jan, Feb, Mar, Apr, Jun, Jul, Aug, Sep, Oct, Nov, Dec};
    {
        ret = "01";
    }
    else if(('F' == temp_month[0]) && ('e' == temp_month[1]) && ('b' == temp_month[2]))
    {
        ret = "02";
    }
    else if(('M' == temp_month[0]) && ('a' == temp_month[1]) && ('r' == temp_month[2]))
    {
        ret = "03";
    }
    else if(('A' == temp_month[0]) && ('p' == temp_month[1]) && ('r' == temp_month[2]))
    {
        ret = "04";
    }
    else if(('M' == temp_month[0]) && ('a' == temp_month[1]) && ('y' == temp_month[2]))
    {
        ret = "05";
    }
    else if(('J' == temp_month[0]) && ('u' == temp_month[1]) && ('n' == temp_month[2]))
    {
        ret = "06";
    }
    else if(('J' == temp_month[0]) && ('u' == temp_month[1]) && ('l' == temp_month[2]))
    {
        ret = "07";
    }
    else if(('A' == temp_month[0]) && ('u' == temp_month[1]) && ('g' == temp_month[2]))
    {
        ret = "08";
    }
    else if(('S' == temp_month[0]) && ('e' == temp_month[1]) && ('p' == temp_month[2]))
    {
        ret = "09";
    }
    else if(('O' == temp_month[0]) && ('c' == temp_month[1]) && ('t' == temp_month[2]))
    {
        ret = "10";
    }
    else if(('N' == temp_month[0]) && ('o' == temp_month[1]) && ('v' == temp_month[2]))
    {
        ret = "11";
    }
    else if(('D' == temp_month[0]) && ('e' == temp_month[1]) && ('c' == temp_month[2]))
    {
        ret = "12";
    }
    else
    {
        ret = "None";
    }

    return ret;
}


std::string DateTime::GetYearNumber(void)
{
    // Format -> "Sun Nov 03 19:37:05 2024\n" (25 characters)
    std::time_t result = std::time(nullptr);
    char full_date[FULL_DATETIME_LENGTH];
    char temp_year[4] = {'\0'};
    std::string ret = "";
 
    std::strncpy(full_date, std::ctime(&result), FULL_DATETIME_LENGTH);
    std::strncpy(temp_year, &full_date[20], 4);             // copy year

    for (int i = 0; i < 4; i++)
    {
        ret = ret + temp_year[i];
    }
    
    return ret;
}
