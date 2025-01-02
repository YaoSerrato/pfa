#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdlib.h>

// #include <cstring>

#include "BudgetOps.hpp"
// #include "DateTime.hpp"
#include "config.h"

#define     OP_ADD_EXPENSE              (1)
#define     OP_DEL_EXPENSE              (2)
#define     OP_SEE_EXPENSES_SUMMARY     (3)
#define     OP_CLOSE_APP                (4)

void print_header(void)
{
    std::cout << std::endl;
    std::cout << "*****************************************************************************************************" << std::endl;
    std::cout << "\tPersonal Finance App" << std::endl;
    std::cout << "\tDeveloped by Yaoctzin Serrato" << std::endl;
    std::cout << "\tv0.0.0.1" << std::endl;
    std::cout << "*****************************************************************************************************" << std::endl;
    std::cout << std::endl;
}
 
int main()
{
    BudgetOps budget_operations;
    std::vector<std::string> operations = {"Add new expense.", "Delete existing expense.", "See summary of expenses.", "Close application."};
    int op_selected;
    bool close_app = false;

    while(true)
    {
        if(budget_operations.cwd_loaded)
        {
            // print main menu
#if CONFIG_CLEAR_SCREEN == CONFIG_ENABLED
            system("CLS");
#endif
            print_header();

            std::cout << budget_operations.recent_op << std::endl << std::endl;

            std::cout << "Current working directory correctly loaded." << std::endl;
            std::cout << "Select which operation you would like to perform:" << std::endl << std::endl;

            for(int i = 0; i < operations.size() ; i++)
            {
                std::cout << std::left;
                std::cout << std::setw(5) << "" << std::setw(10) << std::to_string(i + 1) << std::setw(50) << operations[i] << std::endl;
            }

            std::cout << std::endl << "Select option: ";
            std::cin >> op_selected;

            // check for invalid operation
            if( (op_selected <= 0) || (op_selected > operations.size()) )
            {
                budget_operations.recent_op =  "WARNING: Invalid selection, choose another one.";
                continue;
            }
            else
            {
                budget_operations.recent_op =  "";
            }

            // act accordingly
            switch (op_selected)
            {
                case OP_ADD_EXPENSE:
                    budget_operations.add_expense();
                break;
                
                case OP_DEL_EXPENSE:
                break;
                
                case OP_SEE_EXPENSES_SUMMARY:
                    budget_operations.see_expenses_summary();
                break;
                
                case OP_CLOSE_APP:
                    close_app = true;
                break;
                
                default:
                break;
            }

            // check if app needs to be closed
            if(close_app)
            {
                std::cout << std::endl << "Closing application.";
                break;
            }
            else
            {
            }
        }
        else
        {
            std::cout << "Error while loading the current working directory. Exiting now.";
            break;
        }
    }

    return 0;
}

