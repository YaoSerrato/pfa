#include <cstring>
#include <fstream>
#include <iostream>

#include "DateTime.hpp"
 
int main()
{
    DateTime DT;
    char this_yearmonth[YEARMONTH_LENGTH];
    char *txt_file_extension = ".txt\0";
    char file_name[12] = {'\0'};

    std::fstream myfile;

    // create file for this month
    DT.GetYearMonth(&this_yearmonth);
    strcat(file_name, this_yearmonth);
    strcat(file_name, txt_file_extension);

    myfile.open(file_name, std::ios::out | std::ios::app);
    if(!myfile)
    {
        std::cerr << "Unable to open file.\n";
        return 1; // Return an error code
    }
    myfile.close();

    // look for a Monthly Budget (MB) entry within the file
    myfile.open(file_name, std::ios::in); // Open the file in read mode
    if(!myfile)
    {
        std::cerr << "Unable to open file.\n";
        return 1; // Return an error code
    }

    std::string line;
    bool isMB = false;

    while ( (std::getline(myfile, line)) && (!isMB))
    {
        isMB = ('M' == line.at(0)) && ('B' == line.at(1));
    }

    myfile.close(); // Close the file

    if(isMB)
    {
        std::cout << "There is a monthly budget entry." << std::endl;
    }
    else
    {
        std::cout << "There is NOT a monthly budget entry." << std::endl;
    }

    return 0;
}