#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include "definitions.h"
#include "data_handler.h"
#include "utilitiy.h"
using namespace std;
//declarations
void customer_mode(vector<bank_account> &customers);
void staff_mode(vector<bank_account> &customers, vector<bank_emp> &staff, vector<acc_close_request> &requests);
void manager_mode(vector<manager> &managers, vector<bank_account> &customers, vector<bank_emp> &staff, vector<acc_close_request> &requests);
//main
int main()
{
    vector<bank_account> customers;
    vector<bank_emp> staff;
    vector<acc_close_request> requests;
    vector<manager> managers;
    // demo/trial manager id:101  pass: "mypass123" 
    // demo/trial emp id:1001 pass: "mypasss"
    // demo/trial customer acc:103410001 pass: "demopass"
    system("cls");
    load_customers(customers);
    load_employees(staff);
    load_closure_requests(requests);
    load_managers(managers);

    //main home
    cout << "\n\n";
    cout << "+-----------------------------------------------------+" << endl;
    cout << "|                                                     |" << endl;
    cout << "|         WELCOME TO THE APEX BANKING SYSTEM          |" << endl;
    cout << "|                                                     |" << endl;
    cout << "+-----------------------------------------------------+" << endl;
    cout << "\n";
    int choice;
    do
    {
        cout << "=====================================================" << endl;
        cout << "             ** Select User Action **           " << std::endl;
        cout << "=====================================================" << endl;
        cout << "\n";
        cout << "    1. >>> Customer Login <<<" << endl;
        cout << "    2. >>> Staff/Manager Login   <<<" << endl;
        cout << "    3. --- Exit Program ---" << endl;
        cout << "\n";
        cout << "=====================================================" << endl;
        
        choice = get_valid_input<int>("Enter your choice: ", 1, 3);
        
        switch (choice)
        {
        case 1:
            customer_mode(customers);
            break;
            case 2:
            {
            int choice1;
            do
            {
                cout << "\n=====================================================" << endl;
                cout << "1. Staff Login" << endl;
                cout << "2. Manager Login" << endl;
                cout << "3. Exit this menu" << endl;
                cout << "=====================================================" << endl;
                
                choice1 = get_valid_input<int>("Enter choice: ", 1, 3);
                switch (choice1)
                {
                case 1:
                    staff_mode(customers, staff, requests);
                    break;
                case 2:
                manager_mode(managers, customers, staff, requests);
                    break;
                case 3:
                cout << "Exiting Menu......" << endl;
                break;
                default:
                cout << "ERROR! Invalid Input." << endl;
                break;
                break;
            }
            } while (choice1 != 3);
            break;
        }
        case 3:
            cout << "Exiting Program........" << endl;
            break;
        default:
        cout << "ERROR! Invalid Input" << endl;
        break;
    }
    } while (choice != 3);
    return 0;
}
//definitions, do implement them seperately, in like modes.cpp 
void customer_mode(vector<bank_account> &customers)
{
    int acc_number;
    string pin;
    bool loggedIn = false;
    bank_account *loggedIn_cst = nullptr;
    // login logic.......
    cout << "...........Public MODE..........." << endl;
    cout << "...........Customer LOGIN..........." << endl;
    cout << "Enter Account Number: ";
    cin >> acc_number;
    cout << "Enter PIN: ";
    cin >> pin;

    for (unsigned int i = 0; i < customers.size(); i++)
    {
        bank_account &cst = customers[i];

        if (cst.cst_login(acc_number, pin))
        {
            loggedIn_cst = &cst;
            loggedIn = true;
            break;
        }
    }
    if (!loggedIn)
    {
        cout << "The account number or password may be wrong / not match. Retry!" << endl;
        return;
    }

    int cst_choice;
    cout << "Welcome User!!" << endl;

    do
    {
        cout << "\n=====================================================\n";
        cout << "1. Deposit Money" << endl; // add more ops later...
        cout << "2. Withdraw Money" << endl;
        cout << "3. View Balance" << endl;
        cout << "4. View Account Details" << endl;
        cout << "5. Read Terms and Conditions" << endl;
        cout << "6. Back to Main Menu(Press 6)" << endl;
        cout << "=====================================================" << endl;
        cst_choice = get_valid_input<int>("Enter choice: ", 1, 6);
        double amt;
        switch (cst_choice)
        {
        case 1:
        {

            amt = get_valid_input<double>("Enter the amount to deposit: ", 1, 500000);
            (*loggedIn_cst).deposit_money(amt);
            save_customers_to_file(customers);
            break;
        }
        case 2:
        {
            amt = get_valid_input<double>("Enter the amount to withdraw: ", 1, 500000);
            cout<< "\n Enter you PASSWORD again for verification: ";    // extra security for withdrawals
            string verify_pass;
            cin >> verify_pass;
            if (loggedIn_cst->cst_login(acc_number, verify_pass) == false)
            {
                cout << "Password incorrect! Transaction cancelled. Retry with correct password." << endl;
                break;
            }
            cout << "\nProcessing withdrawal of amount: " << amt << endl;
            (*loggedIn_cst).withdraw_money(amt);
            save_customers_to_file(customers);
            break;
        }
        case 3:
            (*loggedIn_cst).display_balance();
            break;
        case 4:
            (*loggedIn_cst).show_acc_details();
            break;
        case 5:
            (*loggedIn_cst).terms_conditions();
            break;
        case 6:
            cout << "Returning to Main Menu...." << endl;
            break;
        default:
            cout << "Invalid Choice! Please try again." << endl;
            break;
        }
    } while (cst_choice != 6);
}

void staff_mode(vector<bank_account> &customers, vector<bank_emp> &staff, vector<acc_close_request> &requests)
{
    int id;
    string pass;
    bool loggedIn = false;
    bank_emp *loggedIn_emp = nullptr;
    // login logic.......
    cout << "...........STAFF MODE..........." << endl;
    cout << "...........STAFF LOGIN..........." << endl;
    cout << "Enter Employee ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pass;

    for (unsigned int i = 0; i < staff.size(); i++)
    {
        bank_emp &emp = staff[i];
        if (staff[i].get_emp_ID() == id)
        {
            loggedIn_emp = &emp;
            break;
        }
    }
    if (loggedIn_emp == nullptr)
    {
        cout << "=====================================================" << endl;
        cout << "Login failed! Invalid ID or password." << endl;
        return;
    }
    // check if its the first login of employee
    if (loggedIn_emp->get_not_changed_pass())
    {
        // first login of emp
        if (!loggedIn_emp->login(id, pass))
        {
            cout << "=====================================================" << endl;
            cout << "Login failed! Invalid ID or password." << endl;
            return;
        }
        cout << "\n\nWARNING: Temporary Password Detected. MANDATORY PASSWORD CHANGE Required" << endl;

        // calling the public method that handles the pass change loop
        loggedIn_emp->initiate_pass_change();

        // save the vector, after  the change to update the password and the flag in the file!
        save_employees_to_file(staff);
        loggedIn = true;
    }
    else
    { // for subsequent logins...

        string sec_pass = hash_string(pass);
        if (!loggedIn_emp->login(id, sec_pass))
        {
            cout << "=====================================================" << endl;
            cout << "Login failed! Invalid ID or password." << endl;
            return;
        }
        loggedIn = true;
    }
    if (loggedIn)
    {
        int emp_choice;
        cout << "=====================================================" << endl;
        cout << "Welcome, staff member....." << endl;
        do
        {
            cout << "1. Open new Account" << endl; // add more ops later...
            cout << "2. View Account" << endl;
            cout << "3. Update Account Details" << endl;
            cout << "4. Add request to close existing account" << endl;
            cout << "5. Back to Main Menu(Press 5)" << endl;
            emp_choice = get_valid_input<int>("Enter choice: ", 1, 5);

            switch (emp_choice)
            {
            case 1:
                (*loggedIn_emp).open_new_acc(customers);
                break;
            case 2:
                (*loggedIn_emp).view_acc(customers);
                break;
            case 3:
                (*loggedIn_emp).update_acc_info(customers);
                break;
            case 4:
                (*loggedIn_emp).close_acc(customers, requests);
                break;
            case 5:
                cout << "Returning to Main Menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        } while (emp_choice != 5);
    }
    if (!loggedIn)
    {
        cout << "=====================================================" << endl;
        cout << "Login failed! Invalid ID or password." << endl;
        return;
    }
}

void manager_mode(vector<manager> &managers, vector<bank_account> &customers, vector<bank_emp> &staff, vector<acc_close_request> &requests)
{
    string id;
    string pass;
    bool loggedIn = false;
    manager *logged_man = nullptr;
    // login logic.......
    cout << "...........MANAGER MODE..........." << endl;
    cout << "=====================================================" << endl;
    cout << "...........MANAGER LOGIN..........." << endl;
    cout << "Enter Manager ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Password: ";
    cin >> pass;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (unsigned int i = 0; i < managers.size(); i++)
    {
        manager &man = managers[i];
        if (man.get_man_id() == trim(id))
        {
            logged_man = &man;
            break;
        }
    }
    if (logged_man == nullptr)
    {
        cout << "=====================================================" << endl;
        cout << "Login failed! Invalid ID or password." << endl;
        return;
    }
    if (logged_man->get_not_changed_pass())
    {

        if (logged_man->get_man_pass() != trim(pass))
        {
            cout << "=====================================================" << endl;
            cout << "Login failed! Invalid ID or password." << endl;
            return;
        }
        cout << "\n\nWARNING: Temporary Password Detected. MANDATORY PASSWORD CHANGE Required" << endl;

        // calling the public method that handles the pass change loop
        logged_man->initiate_pass_change();
        logged_man->set_man_pass(logged_man->get_emp_pass());
        // save the vector , after the change to update the password and the flag in the file!
        save_managers(managers);
        loggedIn = true;
    }
    else
    {
        // Subsequent login: check_credentials handles hashing detection internally
        if (!logged_man->check_credentials(id, pass))
        {
            cout << "=====================================================" << endl;
            cout << "Login failed! Invalid ID or password." << endl;
            return;
        }
        loggedIn = true; // FIX: was false, now correctly set to true
    }
    // logged in, now continue

    if (loggedIn)
    {
        int man_choice;
        cout << "\n\nWelcome, Manager....." << endl;
        do
        {
            cout << "1. Customer Management" << endl;
            cout << "2. Employee Management" << endl;
            cout << "3. View Balance Sheet/Report" << endl;
            cout << "4. Load New Data" << endl;
            cout << "5. Back to Main Menu(Press 5)" << endl;
            man_choice = get_valid_input<int>("Enter choice: ", 1, 5);

            switch (man_choice)
            {
            case 1:
            {
                int man_choice1;
                do
                {
                    cout << "\n=====================================================" << endl;
                    cout << "\n1. Open new Account" << endl;
                    cout << "2. View Account" << endl;
                    cout << "3. Close Customer Account" << endl;
                    cout << "4. View all Customer Accounts" << endl;
                    cout << "5. Back to Manager Home Menu(Press 5)" << endl;
                    cout << "\n=====================================================" << endl;
                    man_choice1 = get_valid_input<int>("Enter choice: ", 1, 5);
                    switch (man_choice1)
                    {
                    case 1:
                        (*logged_man).open_new_acc(customers);
                        save_customers_to_file(customers);
                        break;
                    case 2:
                        (*logged_man).view_acc(customers);
                        break;
                    case 3:
                        (*logged_man).close_acc(customers, requests);
                        break;
                    case 4:
                        (*logged_man).view_all_customers(customers);
                        break;
                    case 5:
                        cout << "Returning........." << endl;
                        break;
                    default:
                        cout << "Invalid Input." << endl;
                        break;
                    }
                } while (man_choice1 != 5);
                break;
            }
            case 2:
            {
                int man_choice2;
                do
                {
                    cout << "\n=====================================================" << endl;
                    cout << "\n1. Add new Employee" << endl;
                    cout << "2. View Employee Details" << endl;
                    cout << "3. Update Employee Details" << endl;
                    cout << "4. Fire an Employee" << endl;
                    cout << "5. View all Employees" << endl;
                    cout << "6. Back to Manager Home Menu(Press 6)" << endl;
                    cout << "=====================================================" << endl;
                    man_choice2 = get_valid_input<int>("Enter choice: ", 1, 6);
                    switch (man_choice2)
                    {
                    case 1:
                        (*logged_man).hire_new_emp(staff);
                        save_employees_to_file(staff);
                        break;
                    case 2:
                        (*logged_man).view_emp_detail(staff);
                        break;
                    case 3:
                        (*logged_man).update_emp_detail(staff);
                        break;
                    case 4:
                        (*logged_man).fire_emp(staff);
                        break;
                    case 5:
                        (*logged_man).view_all_emps(staff);
                        break;
                    case 6:
                        cout << "Returning to manager menu...." << endl;
                        break;
                    default:
                        break;
                    }
                } while (man_choice2 != 6);
                break;
            }
            case 3:
                cout << "Reports................." << endl; // add options for seeing different reports...
                (*logged_man).view_balancesheet();
                break;
            case 4:
                cout << "Loading data Updates..." << endl;
                (*logged_man).load_data(staff, customers, requests);
                break;
            case 5:
                cout << "Returning to Main Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        } while (man_choice != 5);
    }
}

