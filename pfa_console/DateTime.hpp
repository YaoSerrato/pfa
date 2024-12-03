#include <cassert>
#include <cstring>
#include <ctime>
#include <iostream>

#define     FULL_DATETIME_LENGTH        (25)        // length for a string like "Sun Nov 03 19:37:05 2024\n"
#define     YEARMONTH_LENGTH            (8)         // length for a string like "2024Nov\n"

class DateTime
{
private:

public:
    DateTime();
    ~DateTime();
    void GetFullDateTime(char (*data)[FULL_DATETIME_LENGTH]);
    void GetYearMonth(char (*data)[YEARMONTH_LENGTH]);
    std::string GetMonthNumber(void);
    std::string GetYearNumber(void);
};


