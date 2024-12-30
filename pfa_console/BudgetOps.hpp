#include <cassert>
#include <string>
#include <vector>

#define     BUDOPS_CWD_MAX_LEN     (1024)

using namespace std;

class BudgetOps
{
private:
    void find_budget_records(void);
    bool show_budget_records(void);
    std::string create_budget_record(void);
    void insert_expense(std::string budget_record);

public:
    std::string recent_op = "";
    const std::vector<float> expenses_assigned_percentage = {50, 30, 20};
    const std::vector<std::string> expenses_categories = {"Necessities", "Wants", "Savings/Investments"};
    const std::vector<std::string> expenses_categories_id = {"NE", "WN", "SI"};
    char current_working_directory[BUDOPS_CWD_MAX_LEN] = {'\0'};
    bool cwd_loaded = false;
    std::vector<std::string> budget_files;

    BudgetOps();
    ~BudgetOps();

    void add_expense(void);
    void delete_expense(void);
    void see_expenses_summary(void);
};


