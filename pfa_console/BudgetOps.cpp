#include "BudgetOps.hpp"
#include "DateTime.hpp"
#include "config.h"

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

#define     BO_BUDGET_ENTRY_SEPARATOR       ("#")
#define     BO_BUDGET_ENTRY_TAG             ("bdg")
#define     BO_INCOME_ENTRY_TAG             ("inc")
#define     BO_EXPENSE_ENTRY_TAG            ("exp")

#define     BO_NECESSITIES_INDEX            (0)
#define     BO_WANTS_INDEX                  (1)
#define     BO_SAVINGS_INVESTMENTS_INDEX    (2)


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

    // Clearing the vector
    budget_files.clear();

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

    std::cout << "Record created: " << this_budget_record << std::endl << std::endl;

    
    // adding initial available monthly budget
    float budget = 0;

    std::cout << "Insert initial available monthly budget (can have decimals): ";
    std::cin >> budget;

    myfile.open(file_name, std::ios::out);
    myfile << BO_BUDGET_ENTRY_TAG;
    myfile << BO_BUDGET_ENTRY_SEPARATOR;
    myfile << std::fixed << std::setprecision(2) << budget << std::endl;
    myfile.close();

    return this_budget_record;
}

bool BudgetOps::look_for_monthly_budget(std::string budget_record)
{
    unsigned int n = budget_record.length();
    char file_name[n + 1] = {'\0'};
    std::string line;
    std::fstream myfile;
    bool isBDG = false;

    strcpy(file_name, budget_record.c_str());

    myfile.open(file_name, std::ios::in); // open the file in read mode
    while ( (std::getline(myfile, line)) && (!isBDG))
    {
        isBDG = ('b' == line.at(0)) && ('d' == line.at(1)) && ('g' == line.at(2));
    }
    myfile.close(); // Close the file

    return isBDG;
}

void BudgetOps::insert_expense(std::string budget_record)
{
    std::fstream myfile;
    unsigned int n = budget_record.length();
    char file_name[n + 1] = {'\0'};
    std::string line;
    bool isBDG = false;

    std::string bdg_str = "";
    float bdg_flt = 0;

    strcpy(file_name, budget_record.c_str());

    myfile.open(file_name, std::ios::in); // open the file in read mode
    while ( (std::getline(myfile, line)) && (!isBDG))
    {
        isBDG = ('b' == line.at(0)) && ('d' == line.at(1)) && ('g' == line.at(2));

        if(isBDG)
        {
            bdg_str = line.substr(4, line.length() - 4);
            bdg_flt = std::stof(bdg_str);

            for (unsigned int i = 0; i < expenses_categories.size(); i++)
            {
                std::cout << "\tCategory " << std::to_string(i + 1) << " " << expenses_categories[i] << " was assigned " << expenses_assigned_percentage[i] << "%, equivalent to $" << ((bdg_flt) * (expenses_assigned_percentage[i] / 100)) << std::endl;
            }
            break;
        }
        else
        {
            // should not enter here
        }
    }
    myfile.close(); // Close the file

    // asking user to enter expense details (category, date, amount, description)
    unsigned int category;
    float amount;
    std::string date;
    std::string description;
    bool try_again = true;

    while(try_again)
    {
        std::cout << std::endl << "Enter expense category (by number): ";
        std::cin >> category;
        try_again = (category <= 0) || (category > expenses_categories.size());

        if(try_again)
        {
            std::cout << "Invalid category, choose another one." << std::endl;
        }
        else
        {
            std::cout << "Selected category: " << expenses_categories[category - 1] << std::endl;
        }
    }

    // The issue is that after reading amount with std::cin, there is a leftover newline character
    // in the input buffer that std::getline reads immediately. To fix this, you can add an
    // extra std::cin.ignore() after reading amount to clear the newline character from the input buffer.

    std::cout << "Enter date (DD:MMM:YYYY): " << std::endl;
    std::cin >> date;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character from the input buffer

    std::cout << "Enter expense amount (can have decimals): " << std::endl;
    std::cin >> amount;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character from the input buffer

    std::cout << "Enter description (string with spaces): " << std::endl;
    std::getline(std::cin, description);

    // writing expense to file
    myfile.open(file_name, std::ios::app);
    myfile << BO_EXPENSE_ENTRY_TAG;
    myfile << BO_BUDGET_ENTRY_SEPARATOR;
    myfile << expenses_categories_id[category - 1];
    myfile << BO_BUDGET_ENTRY_SEPARATOR;
    myfile << date;
    myfile << BO_BUDGET_ENTRY_SEPARATOR;
    myfile << std::fixed << std::setprecision(2) << amount; // apparently, I do not need to convert to string
    myfile << BO_BUDGET_ENTRY_SEPARATOR;
    myfile << description << std::endl;
    myfile.close();

    recent_op = "Expense added to record successfully! Exited to main menu.";
}

void BudgetOps::see_summary(std::string budget_record)
{
#if CONFIG_CLEAR_SCREEN == CONFIG_ENABLED
    system("CLS");
#endif
    std::cout << std::endl << "*******************************************************************************************************************************" << std::endl;
    std::cout << "BUDGET" << std::endl;
    std::cout << "*******************************************************************************************************************************" << std::endl;

    std::cout << "Showing expenses summary for budget record: " << budget_record << std::endl << std::endl;

    std::fstream myfile;
    unsigned int n = budget_record.length();
    char file_name[n + 1] = {'\0'};
    std::string line;
    bool isBDG = false;

    std::string bdg_str = "";
    float bdg_flt = 0;

    strcpy(file_name, budget_record.c_str());

    myfile.open(file_name, std::ios::in); // open the file in read mode
    while ( (std::getline(myfile, line)) && (!isBDG))
    {
        isBDG = ('b' == line.at(0)) && ('d' == line.at(1)) && ('g' == line.at(2));

        if(isBDG)
        {
            bdg_str = line.substr(4, line.length() - 4);
            bdg_flt = std::stof(bdg_str);

            std::cout << "Available monthly budget: $" << bdg_flt << std::endl << std::endl;
            std::cout << "Available categories: " << std::endl;
            std::cout << std::setw(10) << "" << std::setw(25) << "CATEGORY" << std::setw(15) << "PERCENTAGE" << std::setw(20) << "AMOUNT" << std::endl;

            for (unsigned int i = 0; i < expenses_categories.size(); i++)
            {
                std::cout << std::setw(10) << "" << std::setw(25) << expenses_categories[i] << std::setw(15) << expenses_assigned_percentage[i] << std::setw(20) << ((bdg_flt) * (expenses_assigned_percentage[i] / 100)) << std::endl;
            }
            break;
        }
        else
        {
            // should not enter here
        }
    }
    myfile.close(); // Close the file

    // showing expenses
    std::cout << std::endl << "*******************************************************************************************************************************" << std::endl;
    std::cout << "EXPENSES" << std::endl;
    std::cout << "*******************************************************************************************************************************" << std::endl;

    std::string temp;
    int index = 0;
    std::cout << std::endl << std::endl;
    line.clear();
    float total_expenses[expenses_categories.size()] = {0};

    for (int i = 0; i < expenses_categories_id.size(); i++)
    {
        std::cout << "Expenses for category: " << expenses_categories[i] << std::endl;

        myfile.open(file_name, std::ios::in); // open the file in read mode
        while (std::getline(myfile, line))
        {
            if(line.substr(4, 2) == expenses_categories_id[i])
            {
                // print date
                temp = line.substr(7, line.length() - 7);
                index = temp.find(BO_BUDGET_ENTRY_SEPARATOR);
                std::cout << std::setw(10) << "" << std::setw(25) << temp.substr(0, index);

                // print amount
                index = index + 1;
                temp = temp.substr(index, temp.length() - index);
                index = temp.find(BO_BUDGET_ENTRY_SEPARATOR);
                std::cout << std::setw(20) << temp.substr(0, index);
                total_expenses[i] += std::stof(temp.substr(0, index));

                // print description
                index = index + 1;
                temp = temp.substr(index, temp.length() - index);
                std::cout << std::setw(20) << temp << std::endl;
            }
            else
            {
                // not from this category
            }
        }
        myfile.close(); // Close the file
        std::cout << std::endl;
    }

    // showing overall balance
    std::cout << std::endl << "*******************************************************************************************************************************" << std::endl;
    std::cout << "BALANCE" << std::endl;
    std::cout << "*******************************************************************************************************************************" << std::endl;

    std::cout << std::endl << std::endl;
    std::cout << "Overall balance: " << std::endl;
    std::cout << std::setw(10) << "" << std::setw(25) << "CATEGORY" << std::setw(20) << "ASSIGNED" << std::setw(20) << "SPENT" << std::setw(20) << "AVAILABLE" << std::setw(20) << "SPENT (%)" << std::endl;

    for (int i = 0; i < expenses_categories_id.size(); i++)
    {
        std::cout << std::setw(10) << "" << std::setw(25) << expenses_categories[i];
        std::cout << std::setw(20) << ((bdg_flt) * (expenses_assigned_percentage[i] / 100));
        std::cout << std::setw(20) << total_expenses[i];
        std::cout << std::setw(20) << ((bdg_flt) * (expenses_assigned_percentage[i] / 100)) - total_expenses[i];
        std::cout << std::setw(20) << ((total_expenses[i] / ((bdg_flt) * (expenses_assigned_percentage[i] / 100))) * 100) << std::endl;
    }

    // wait for user input to exit to main menu
    std::cout << std::endl << std::endl;
    int number;
    std::cout << "Enter a number to exit to main menu: ";
    std::cin >> number;
}

void BudgetOps::add_expense(void)
{
    bool records_found =  false;
    int chosen_record;
    std::string this_budget_record = "";
    bool try_again = true;
    std::fstream myfile;

#if CONFIG_CLEAR_SCREEN == CONFIG_ENABLED
    system("CLS");
#endif

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
        std::cout << "Selected record: " << this_budget_record << std::endl << std::endl;
    }
    else
    {
        // create a new budget record
        this_budget_record = create_budget_record();
        std::cout << "Selected record: " << this_budget_record << std::endl << std::endl;
    }

    // check if budget record has a monthly budget entry
    bool isBDG = false;
    isBDG = look_for_monthly_budget(this_budget_record);

    if(isBDG)
    {
        insert_expense(this_budget_record);
    }
    else
    {
        recent_op = "WARNING: There is not any monthly budget entry in the budget record.\n 'Add expense' operation was aborted. Exited to main menu.";
    }
}

void BudgetOps::see_expenses_summary(void)
{
    bool records_found =  false;
    bool try_again = true;
    int chosen_record;
    std::string this_budget_record = "";
    std::fstream myfile;

#if CONFIG_CLEAR_SCREEN == CONFIG_ENABLED
    system("CLS");
#endif

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
        std::cout << "Selected record: " << this_budget_record << std::endl << std::endl;

        // check if budget record has a monthly budget entry
        bool isBDG = false;
        isBDG = look_for_monthly_budget(this_budget_record);

        if(isBDG)
        {
            see_summary(this_budget_record);
        }
        else
        {
            recent_op = "WARNING: There is not any monthly budget entry in the budget record.\n 'See summary of expenses' operation was aborted. Exited to main menu.";
        }
    }
    else
    {
        // there is not any budget record, so we cannot show any summary
        recent_op = "WARNING: There is not any budget record yet, so a summary cannot be shown. Exited to main menu.";
    }
}
