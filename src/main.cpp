#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include "definitions.h"
#include "data_handler.h"
using namespace std;

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
        cout << "\n=====================================================";
        cout << "1. Deposit Money" << endl; // add more ops later...
        cout << "2. Withdraw Money" << endl;
        cout << "3. View Balance" << endl;
        cout << "4. View Account Details" << endl;
        cout << "5. Read Terems and Conditions" << endl;
        cout << "6. Back to Main Menu(Press 6)" << endl;
        cout << "=====================================================" << endl;
        cin >> cst_choice;
        double amt;
        switch (cst_choice)
        {
        case 1:
        {
            cout << "Enter the amount to deposit" << endl;
            cin >> amt;
            (*loggedIn_cst).deposit_money(amt);
            break;
        }
        case 2:
        {
            cout << "Enter the amount to withdraw" << endl;
            cin >> amt;
            (*loggedIn_cst).withdraw_money(amt);
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

void staff_mode(vector<bank_account> &customers, vector<bank_emp> &staff, vector<Acc_Close_Request> &requests)
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

        if (emp.login(id, pass))
        {
            loggedIn_emp = &emp;
            loggedIn = true;
            break;
        }
    }

    if (!loggedIn)
    {
        cout << "=====================================================" << endl;
        cout << "Login failed! Invalid ID or password." << endl;
        return;
    }
    // logged in, now continue
    int emp_choice;
    cout << "=====================================================" << endl;
    cout << "Welcome, staff member....." << endl;
    cout << "Opened Accounts..." << endl;
    do
    {
        cout << "1. Open new Account" << endl; // add more ops later...
        cout << "2. View Account" << endl;
        cout << "3. Update Account Details" << endl;
        cout << "4. Add request to close existing account" << endl;
        cout << "5. Back to Main Menu(Press 5)" << endl;
        cin >> emp_choice;

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

void manager_mode(manager &manager, vector<bank_account> &customers, vector<bank_emp> &staff, vector<Acc_Close_Request> &requests)
{
    int id;
    string pass;
    bool loggedIn = false;
    // login logic.......
    cout << "...........MANAGER MODE..........." << endl;
    cout << "=====================================================" << endl;
    cout << "...........MANAGER LOGIN..........." << endl;
    cout << "Enter Manager ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pass;
    if (manager.check_credentials(id, pass))
    {
        loggedIn = true;
    }
    if (!loggedIn)
    {
        cout << "=====================================================" << endl;
        cout << "Login failed! Invalid Manager ID or password." << endl;
        return;
    }
    // logged in, now continue
    int man_choice;
    cout << "\n\nWelcome, Manager....." << endl;
    do
    {
        cout << "1. Customer Management" << endl;
        cout << "2. Employee Management" << endl;
        cout << "3. View Balance Sheet/Report" << endl;
        cout << "4. Back to Main Menu(Press 4)" << endl;
        cin >> man_choice;

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
                cin >> man_choice1;
                switch (man_choice1)
                {
                case 1:
                    manager.open_new_acc(customers);
                    save_customers_to_file(customers);
                    break;
                case 2:
                    manager.view_acc(customers);
                    break;
                case 3:
                    manager.close_acc(customers, requests);
                    break;
                case 4:
                    manager.view_all_customers(customers);
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
                cin >> man_choice2;
                switch (man_choice2)
                {
                case 1:
                    manager.hire_new_emp(staff);
                    save_employees_to_file(staff);
                    break;
                case 2:
                    manager.view_emp_detail(staff);
                    break;
                case 3:
                    manager.update_emp_detail(staff);
                    break;
                case 4:
                    manager.fire_emp(staff);
                    break;
                case 5:
                    manager.view_all_emps(staff);
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
            manager.view_balancesheet();
            break;
        case 4:
            cout << "Returning to Main Menu..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (man_choice != 4);
}
int main()
{
    vector<bank_account> customers;
    vector<bank_emp> staff;
    vector<Acc_Close_Request> requests;

    manager m1(0000, "securepass");
    manager m2(0100, "kushalpass");
    system("cls");
    load_customers(customers);
    load_employees(staff);
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
        cout << "Enter your choice: ";

        std::cin >> choice;

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
                cin >> choice1;
                switch (choice1)
                {
                case 1:
                    staff_mode(customers, staff, requests);
                    break;
                case 2:
                    manager_mode(m1, customers, staff, requests);
                    break;
                case 3:
                    cout << "Exiting Menu......" << endl;
                    break;
                default:
                    cout << "ERROR! Invalid Input." << endl;
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
