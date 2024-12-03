#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdlib.h>

// #include <cstring>
// #include <fstream>

#include "BudgetOps.hpp"
// #include "DateTime.hpp"

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
    std::string recent_op = "";
    bool close_app = false;

    while(true)
    {
        if(budget_operations.cwd_loaded)
        {
            // print main menu
            //system("CLS");
            print_header();

            std::cout << recent_op << std::endl << std::endl;

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
                recent_op =  "Invalid selection, choose another one.";
                continue;
            }
            else
            {
                recent_op =  "";
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

    // DateTime DT;
    // char this_yearmonth[YEARMONTH_LENGTH];
    // char *txt_file_extension = ".txt\0";
    // char file_name[12] = {'\0'};

    // std::fstream myfile;

    // // create file for this month
    // DT.GetYearMonth(&this_yearmonth);
    // strcat(file_name, this_yearmonth);
    // strcat(file_name, txt_file_extension);

    // myfile.open(file_name, std::ios::out | std::ios::app);
    // if(!myfile)
    // {
    //     std::cerr << "Unable to open file.\n";
    //     return 1; // Return an error code
    // }
    // myfile.close();

    // // look for a Monthly Budget (MB) entry within the file
    // myfile.open(file_name, std::ios::in); // Open the file in read mode
    // if(!myfile)
    // {
    //     std::cerr << "Unable to open file.\n";
    //     return 1; // Return an error code
    // }

    // std::string line;
    // bool isMB = false;

    // while ( (std::getline(myfile, line)) && (!isMB))
    // {
    //     isMB = ('M' == line.at(0)) && ('B' == line.at(1));
    // }

    // myfile.close(); // Close the file

    // if(isMB)
    // {
    //     std::cout << "There is a monthly budget entry." << std::endl;
    // }
    // else
    // {
    //     std::cout << "There is NOT a monthly budget entry." << std::endl;
    // }

    return 0;
}



// #include <iostream>
// #include <fstream>
// #include <string>

// int main() {
//     // The file path stored in a std::string
//     std::string filePath = "path/to/your/output.txt";
//     std::string content = "Hello, this is a text file created using a file path stored in a std::string.";

//     // Create an ofstream object using the file path from the string
//     std::ofstream outFile(filePath);

//     // Check if the file was successfully opened
//     if (!outFile) {
//         std::cerr << "Error opening file at " << filePath << " for writing!" << std::endl;
//         return 1;
//     }

//     // Write the content to the file
//     outFile << content;

//     // Close the file
//     outFile.close();

//     std::cout << "File created at " << filePath << " and content written." << std::endl;

//     return 0;
// }
