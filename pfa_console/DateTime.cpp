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
