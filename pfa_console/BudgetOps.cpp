#include "BudgetOps.hpp"
#include "DateTime.hpp"

#include <iostream>
#include <iomanip>
#include <direct.h>
#include <fstream>

#include <filesystem>
#include <string>
#include <sys/stat.h>

#define     BO_BUDGET_RECORD_FILE_EXT       (".txt")
#define     BO_BUDGET_RECORD_FILE_TAG       ("budrec")
#define     BO_UNDERSCORE                   ("_")


BudgetOps::BudgetOps()
{
    // call _getcwd to get the current working directory and store it in buffer
    if(getcwd(current_working_directory, BUDOPS_CWD_MAX_LEN) != NULL)
    {
        // print the current working directory
        cwd_loaded = true;
        //std::cout << "Current working directory: " << current_working_directory << std::endl;
    } 
    else
    {
        // If _getcwd returns NULL, print an error message
        cwd_loaded = false;
        //std::cerr << "Error getting current working directory" << std::endl;
    }
}


BudgetOps::~BudgetOps()
{
}


void BudgetOps::find_budget_records(void)
{
    // This structure would distinguish a file from a directory
    struct stat sb;
    std::string file_ext = BO_BUDGET_RECORD_FILE_EXT;
    std::string file_tag = BO_BUDGET_RECORD_FILE_TAG;

    std::cout << std::endl << "Looking for budget records..." << std::endl;

    // Looping until all the items of the directory are exhausted
    for (const auto& entry : std::filesystem::directory_iterator(current_working_directory))
    {
        // Converting the path to const char * in the subsequent lines
        std::filesystem::path outfilename = entry.path();
        std::string outfilename_str = outfilename.string();
        const char* path = outfilename_str.c_str();

        // Testing whether the path points to a non-directory or not If it does, displays path
        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
        {
            if( (outfilename_str.find(file_ext) != std::string::npos) && (outfilename_str.find(file_tag) != std::string::npos) )
            {
                // One budget record found, add it.
                budget_files.push_back(outfilename_str);
                //std::cout << outfilename_str << std::endl;
            }
            else
            {
            }
        }
        else
        {
        }
    }
}


bool BudgetOps::show_budget_records(void)
{
    bool ret = false;

    if(budget_files.empty())
    {
        // there is not any budget file yet.
        std::cout << "There is not any budget record yet." << std::endl;
        ret = false;
    }
    else
    {
        // show found budget files
        std::cout << "Budget records available are: " << std::endl;

        for (int i = 0; i < budget_files.size(); i++)
        {
            std::cout << std::left;
            std::cout << std::setw(10) << "" << std::setw(10) << std::to_string(i + 1) << std::setw(50) << budget_files[i] << std::endl;
        }
        ret = true;
    }

    return ret;
}

std::string BudgetOps::create_budget_record(void)
{
    unsigned int creation_option;
    bool try_again = true;
    std::string this_budget_record = "";
    int i = 0;
    std::string current_month;
    std::string current_year;
    DateTime DT;
    unsigned int input_month;
    unsigned int input_year;

    std::cout << "Creating a new budget record." << std::endl;

    while(try_again)
    {
        std::cout << std::endl << "Enter 1 for automatically creating it (for the current month) or 2 for creating it manually: ";
        std::cin >> creation_option;
        try_again = (creation_option <= 0) || (creation_option > 2);

        if(try_again)
        {
            std::cout << "Invalid selection, choose again." << std::endl;
        }
    }

    // creating budget record file
    while(current_working_directory[i] != '\0')
    {
        this_budget_record = this_budget_record + current_working_directory[i];
        i++;
    }

    this_budget_record = this_budget_record + "\\";

    if(1 == creation_option)
    {
        // create automatically
        current_month = DT.GetMonthNumber();
        current_year = DT.GetYearNumber();
    }
    else if( 2 == creation_option)
    {
        // create manually
        try_again = true;
        while(try_again)
        {
            std::cout << std::endl << "Enter month (1 to 12): ";
            std::cin >> input_month;
            try_again = (input_month <= 0) || (input_month > 12);

            if(try_again)
            {
                std::cout << "Invalid month, try again." << std::endl;
            }
        }

        try_again = true;
        while(try_again)
        {
            std::cout << std::endl << "Enter year (0 to 9999): ";
            std::cin >> input_year;
            try_again = (input_year < 0) || (input_year > 9999);

            if(try_again)
            {
                std::cout << "Invalid year, try again." << std::endl;
            }
        }

        current_month = std::to_string(input_month);
        current_year = std::to_string(input_year);
    }
    else
    {
        // we should not arrive here
    }

    this_budget_record = this_budget_record + BO_BUDGET_RECORD_FILE_TAG + BO_UNDERSCORE + current_month + BO_UNDERSCORE + current_year + BO_BUDGET_RECORD_FILE_EXT;
    std::cout << "Record to create: " << this_budget_record << std::endl;

    unsigned int n = this_budget_record.length();
    char file_name[n + 1] = {'\0'};
    std::fstream myfile;

    strcpy(file_name, this_budget_record.c_str());

    myfile.open(file_name, std::ios::out | std::ios::app);
    myfile.close();

    return this_budget_record;
}

void BudgetOps::add_expense(void)
{
    bool records_found =  false;
    int chosen_record;
    std::string this_budget_record = "";
    bool try_again = true;

    // look for existing budget records and show them to the user
    find_budget_records();
    records_found = show_budget_records();

    if(records_found)
    {
        // ask user to select a budget record
        while(try_again)
        {
            std::cout << std::endl << "Select record file (by number): ";
            std::cin >> chosen_record;
            try_again = (chosen_record <= 0) || (chosen_record > budget_files.size());

            if(try_again)
            {
                std::cout << "Invalid selection, choose another one." << std::endl;
            }
        }
        this_budget_record = budget_files[chosen_record - 1];
        std::cout << "Selected record: " << this_budget_record << std::endl;
    }
    else
    {
        // create a new budget record
        this_budget_record = create_budget_record();
    }
}