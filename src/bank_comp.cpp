#include "definitions.h"
#include "data_handler.h"
#include "utilitiy.h"
#include <vector>
#include <iostream>
#include <limits>
#include <ctime>
#include <sstream>
using namespace std;
string get_date()
{
    time_t now = time(0);

    tm *ltm = localtime(&now);

    stringstream ss;

    // The tm structure stores:
    // tm_mday for the day of the month (1-31)
    // tm_mon for the month (0-11)
    // tm_year for the years since 1900
    ss << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year;

    return ss.str();
}
// User Methods
int bank_account::nextAccountNumber = 103410000;

bool bank_account::cst_login(const int accnum, const string pin)
{
    string pass_hash = hash_string(pin);
    return ((user_pass == pass_hash) && (acc_num == accnum));
}
void bank_account::deposit_money(double amt)
{
    balance = balance + amt;
    cout << "Rs." << amt << " deposited successfully in you bank account." << endl; // ending with ...096
}
void bank_account::withdraw_money(double amt)
{
    if (balance > amt && balance - amt > 500)
    {
        balance = balance - amt;
        cout << "Rs." << amt << " withdrawn successfully from your bank account." << endl;
    }
    else if (balance > amt && balance - amt <= 500)
    {
        cout << "ERROR!, " << endl
             << "Can't withdraw, you must maintain a minimum balance." << endl;
    }
    else
    {
        cout << "ERROR!, Insufficient balance, can't withdraw" << endl;
    }
}

void bank_account::display_balance() const
{

    cout << "BALANCE: Rs." << balance << endl; // \u20B9 for rupee sign
}
void bank_account::show_acc_details() const
{
    cout << "Name: " << holder_name << endl;
    cout << "Account Number: " << acc_num << endl;
    cout << "Balance: Rs." << balance << endl;
    cout << "Account type: " << acc_type;
    cout << endl;
    cout << "Email Address: " << email_add << endl;
}
void bank_account::show_short_detail() const
{
    cout << "Account Name: " << acc_num;
    cout << "  Name: " << holder_name;
    cout << "  Account Balance: " << balance << endl;
}
void bank_account::terms_conditions()
{

    cout << "Terms and Conditions" << endl;
    cout << "......................" << endl;
}
void bank_account::setName(string holderName)
{
    holder_name = holderName;
}
void bank_account::setEmail(string newEmail)
{
    email_add = newEmail;
}
void bank_account::setDob(string newDob)
{
    date_of_birth = newDob;
}
void bank_account::setAccType(string accType)
{
    acc_type = accType;
}

// Employees Methods
int bank_emp::next_emp_ID = 1000;
bool bank_emp::login(const int id, const string pass)
{
    return (emp_ID == id && emp_pass == pass);
}
void bank_emp::open_new_acc(vector<bank_account> &customers)
{
    string name;
    string email_id;
    double init_balance = 0.0;
    string dob;
    string acc_type;
    int chooser = 1;
    string pin;
    string secure_pass;
    cout << ".....OPEN NEW ACCOUNT....." << endl;
    cin.clear();
    cout << "Enter the customer name:- " << endl;
    getline(cin, name);
    cout << "Enter " << name << "'s email ID:- " << endl;
    getline(cin, email_id);
    cout << "Enter " << name << "'s Date of Birth(DD/MM/YYYY):- " << endl;
    getline(cin, dob);
    do
    {
        cout << "Enter the " << name << "'s account type:- " << endl;
        cout << "1. Savings Account(Press 1) \n2. Current Account(Press 2)" << endl;
        cin >> chooser;
    } while (chooser != 1 && chooser != 2);
    if (chooser == 1)
        acc_type = "Saving";
    else
    {
        acc_type = "Current";
    }
    cout << "Enter the initial deposit:- " << flush;
    cin >> init_balance;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Kindly ask the user to generate a PIN:- " << endl;
    cout << "Hey, " << name << "! Kindly set your account password (REMEMBER IT): " << flush;
    cin >> pin;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    secure_pass = hash_string(pin);
    bank_account new_account(name, init_balance, email_id, dob, acc_type, secure_pass);
    customers.push_back(new_account);
    save_customers_to_file(customers);
    cout << "=====================================================" << endl;
    cout << "Account created successfully with account number " << new_account.getaccnum() << endl;
}

void bank_emp::view_acc(const vector<bank_account> &customers)
{
    int acc_number;
    bool acc_found = false;
    acc_number = get_valid_input<int>("Enter account number to view: ", 10000, 103412000); // 1000 customers (for now?)

    for (unsigned int i = 0; i < customers.size(); i++)
    {
        if (customers[i].getaccnum() == acc_number)
        {
            customers[i].show_acc_details();
            acc_found = true;
        }
    }
    if (!acc_found)
    {
        cout << "ERROR! Account number not found." << endl;
    }
}

void bank_emp::update_acc_info(vector<bank_account> &customers)
{
    int acc_number;
    // bool acc_found = false;
    bank_account *acc_to_update = nullptr;
    acc_number = get_valid_input<int>("Enter account number to update: ", 10000, 103412000); // 1000 customers (for now?)

    for (unsigned int i = 0; i < customers.size(); i++)
    {
        if (customers[i].getaccnum() == acc_number)
        {
            customers[i].show_acc_details();
            acc_to_update = &customers[i];
            // acc_found = true;
        }
    }
    if (acc_to_update != nullptr)
    {
        int choice;
        do
        {
            cout << "\nWhat would you like to update?" << endl;
            cout << "1. Name" << endl;
            cout << "2. Email Address" << endl;
            cout << "3. Date of Birth" << endl;
            cout << "4. Account Type" << endl;
            cout << "5. Exit Update Menu" << endl;
            choice = get_valid_input<int>("Enter your choice: ", 1, 5);

            switch (choice)
            {
            case 1:
            {
                string newName;
                cin.clear();
                cout << "Enter the new name:-" << endl;
                getline(cin, newName);
                (*acc_to_update).setName(newName);
                save_customers_to_file(customers);
                cout << " Name updated successfully." << endl;
                break;
            }
            case 2:
            {
                string newEmail;
                cout << "Enter the new email:- " << endl;
                cin.clear();
                getline(cin, newEmail);
                (*acc_to_update).setEmail(newEmail);
                save_customers_to_file(customers);
                cout << " Email updated successfully." << endl;
                break;
            }
            case 3:
            {
                string newDob;
                cout << "Enter the new date of birth:- " << endl;
                cin.clear();
                getline(cin, newDob);
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                (*acc_to_update).setDob(newDob);
                save_customers_to_file(customers);
                cout << " DOB updated successfully." << endl;
                break;
            }
            case 4:
            {
                int chooser;
                string acc_type;
                do
                {
                    cout << "Enter the new account type:- " << endl;
                    cout << "1. Savings Account(Press 1) \n2. Current Account(Press 2)" << endl;
                    cin >> chooser;
                } while (chooser != 1 && chooser != 2);
                if (chooser == 1)
                    acc_type = "Saving";
                else
                    acc_type = "Current";

                (*acc_to_update).setAccType(acc_type);
                save_customers_to_file(customers);
                cout << " Account type updated successfully." << endl;
                break;
            }
            case 5:
            {
                cout << "Exiting Update Menu..." << endl;
                break;
            }
            default:
                cout << "ERROR! Invalid Input" << endl;
                break;
            }
        } while (choice != 5);
    }
    else
    {
        {
            cout << "ERROR! Account number not found." << endl;
        }
    }
}
void bank_emp::close_acc(vector<bank_account> &customers, vector<acc_close_request> &requests)
{
    int acc_number = 0;
    bool acc_found = false;
    // bank_account *acc_to_remove = nullptr;
    acc_number = get_valid_input<int>("Enter account number to be closed: ", 10000, 103412000); // 1000 customers (for now?)

    for (unsigned int i = 0; i < customers.size(); i++)
    {
        if (customers[i].getaccnum() == acc_number)
        {
            // acc_to_remove = &customers[i];
            acc_found = true;
        }
    }

    if (!acc_found)
    {
        cout << "ERROR! Account number not found." << endl;
        return;
    }

    acc_close_request new_Request(acc_number, emp_ID, emp_name); // constructor call

    requests.push_back(new_Request);
    save_closure_requests(requests);
    cout << "Request to close account " << acc_number << " sent for manager approval." << endl;
}
void bank_emp::show_emp_detail_man() const
{
    cout << "Employee's Full Name: " << emp_name << endl;
    cout << "Employee ID: " << emp_ID << endl;
    cout << "Date of Hiring: " << date_of_hire << endl;
    cout << "Employee's Phone: " << emp_phone_num << endl;
    cout << "Employee's Email Address: " << emp_email << endl;
    cout << "Employee's Monthly Salary: " << monthly_salary << endl;
    cout << "Employee's Salary Increment per annum: " << increment_pa << endl;
}
void bank_emp::show_emp_detail_emp() const
{
    cout << "Hi, " << emp_name << "..." << endl;
    cout << "Employee's Full Name: " << emp_name << endl;
    cout << "Employee ID: " << emp_ID << endl;
    cout << "Date of Joining: " << date_of_hire << endl;
    cout << "Employee's Phone: " << emp_phone_num << endl;
    cout << "Employee's Email Address: " << emp_email << endl;
    cout << "Employee's Monthly Salary: " << monthly_salary << endl;
}
void bank_emp::show_short_detail() const
{
    cout << "Emp ID: " << emp_ID;
    cout << " | Emp Name: " << emp_name;
    cout << " | Date of hiring: " << date_of_hire;
}
void bank_emp::set_emp_name(string name)
{
    emp_name = name;
}
void bank_emp::set_emp_phone(string phone)
{
    emp_phone_num = phone;
}
void bank_emp::set_emp_email(string email)
{
    emp_email = email;
}
void bank_emp::set_emp_salary(double salary)
{
    monthly_salary = salary;
}
void bank_emp::set_emp_hike(float percent)
{
    increment_pa = percent;
}
void bank_emp::initiate_pass_change()
{
    string newPass1, newPass2;
    string store_pass;
    cout << "\nInitiating mandatory password change." << std::endl;
    do
    {
        cout << "Enter NEW Password (min 6 chars): ";
        cin >> newPass1;
        cout << "Confirm NEW Password: ";
        cin >> newPass2;

        if (newPass1 == newPass2 && newPass1.length() >= 6)
        {
            store_pass = hash_string(newPass1);
            if (typeid(*this) == typeid(bank_emp))
            {
                set_pass(store_pass); // Calling the private mf,
            }
            else if (typeid(*this) == typeid(manager))
            {
                 
            }

            cout << "Password updated successfully. Access granted." << std::endl;
            break;
        }
        else
        {
            cout << "Passwords do not match or are too short. Please try again." << std::endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);
}

// Manager methods
manager::manager(string ID, string pass, bool changed) : bank_emp("Manager ", "01/01/2000", "000", "manager@bank.com", "01/01/1970", 0.0, 0.0f, pass)
{
    manager_ID = ID;
    // Store pass AS-IS (may be plain text on first load, or hashed after password change)
    manager_pass = pass;
    // set the base-class flag according to 'changed'
    not_changed_pass = changed;
}

bool manager::check_credentials(const string ID, const string &pass)
{
    string cleanId = trim(ID);
    string cleanPass = trim(pass);

    if (cleanId != manager_ID) return false;

    // Always hash input and compare to stored (always-hashed) password
    return hash_string(cleanPass) == manager_pass;
}
void manager::set_man_pass(const string &p)
{
    // update base-class stored password and flag
    set_pass(p);            // sets emp_pass and not_changed_pass=false
    manager_pass = p;       // keep manager_pass in sync
}
// void manager::open_new_acc(vector<bank_account> &customers)
//  {
//      string name;
//      string email_id;
//      double init_balance = 0;
//      string dob;
//      int chooser;
//      string acc_type;
//      string pin;
//      cout << ".....OPEN NEW ACCOUNT....." << endl;
//      cout << "";
//      std::cin.clear();
//      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//      cout << "Enter the customer name:- " << flush;
//      getline(cin, name);
//      cout << "Enter " << name << "'s email ID:- " << flush;
//      getline(cin, email_id);
//      cout << "Enter " << name << "'s Date of Birth(MM/DD/YYYY):- " << flush;
//      getline(cin, dob);
//      do
//      {
//          cout << "Enter the " << name << "'s account type:- " << endl;
//          cout << "1. Savings Account(Press 1) \n2. Current Account(Press 2)" << endl;
//          cin >> chooser;
//      } while (chooser != 1 && chooser != 2);
//      if (chooser == 1)
//          acc_type = "Saving";
//      else
//          acc_type = "Current";
//      cout << "Enter the initial deposit:- " << flush;
//      cin >> init_balance;
//      cin.clear();
//      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//      cout << "Kindly ask the user to generate a PIN:- " << endl;
//      cout << "Hey, " << name << "! Kindly set your account password (REMEMBER IT): " << flush;
//      cin >> pin;
//      cin.clear();
//      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//      bank_account new_account(name, init_balance, email_id, dob, acc_type, pin);
//      customers.push_back(new_account);
//      save_customers_to_file(customers);
//      cout << "=====================================================" << endl;
//      cout << "Account created successfully with account number " << new_account.getaccnum() << endl;
//  }

// void manager::view_acc(const vector<bank_account> &customers)
//  {
//      int acc_number;
//      bool acc_found = false;
//      cout << "Enter account number to view:- " << endl;
//      acc_number = get_valid_input<int>("Enter account number to view:", 10000, 103412000);
//      for (unsigned int i = 0; i < customers.size(); i++)
//      {
//          if (customers[i].getaccnum() == acc_number)
//          {
//              customers[i].show_acc_details();
//              acc_found = true;
//          }
//      }
//      if (!acc_found)
//      {
//          cout << "ERROR! Account number not found." << endl;
//      }
//  }
void manager::close_acc(vector<bank_account> &customers, vector<acc_close_request> &requests)
{
    int man_choice;
    do
    {
        cout << "Select Action:- " << endl;
        cout << "1. Review Pending Account Closure Requests" << endl;
        cout << "2. Close an account" << endl;
        cout << "3. Back to Manager Menu" << endl;
        man_choice = get_valid_input<int>("Enter choice: ", 1, 3);
        if (cin.fail())
        {
            cout << "Error: Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        else
        {
            switch (man_choice)
            {
            case 1:
            {
                if (requests.empty())
                {
                    cout << "No Pending Requests." << endl;
                }

                for (unsigned int i = 0; i < requests.size(); i++)
                {
                    cout << i + 1 << ". Account: " << requests[i].get_acc_num() << endl;
                    cout << " Requested by: " << requests[i].get_emp_ID() << " -- " << requests[i].get_emp_name() << endl;
                }
                unsigned int choice;
                cout << "Enter the index of the request to approve (or 0 to cancel): ";
                cin >> choice;

                if (choice > 0 && choice <= requests.size())
                {
                    int accToClose = requests[choice - 1].get_acc_num();
                    for (unsigned int i = 0; i < customers.size(); i++)
                    {
                        if (customers[i].getaccnum() == accToClose)
                        {
                            customers.erase(customers.begin() + i);
                            save_customers_to_file(customers);
                            break;
                        }
                    }
                    requests.erase(requests.begin() + (choice - 1));
                    cout << "Account " << accToClose << " successfully closed." << endl;
                }
                else if (choice == 0)
                {
                    cout << "Cancelling......." << endl;
                    break;
                }
                break;
            }
            case 2:
            {
                bool found = false;
                int acc_num;

                do
                {
                    cout << "Enter the account number to close: ";
                    acc_num = get_valid_input<int>("Enter account number to view:", 10000, 103412000);

                    if (cin.fail())
                    {
                        cout << "Error: Invalid input. Please enter a number." << std::endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    else
                    {
                        break; // Exit the loop if input is a valid number
                    }
                } while (true);

                for (unsigned int i = 0; i < customers.size(); i++)
                {
                    if (acc_num == customers[i].getaccnum())
                    {
                        found = true;
                        customers.erase(customers.begin() + i);
                        save_customers_to_file(customers);
                        cout << "Account " << acc_num << " successfully closed." << endl;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "Account not found." << endl;
                    break;
                }
                break;
            }
            case 3:
            {
                cout << "Returning....." << endl;
                break;
            }
            default:
                cout << "Invalid Input." << endl;
                break;
            }
        }
    } while (man_choice != 3);
}
void manager::view_all_customers(const vector<bank_account> customers)
{
    int total_customers = customers.size();
    if (customers.empty())
    {
        cout << "No customer data available yet." << endl;
    }
    int man_subchoice;
    cout << "\n Total Customers = " << total_customers << endl;
    cout << "Press 1 to see the full customers list." << endl;
    cin >> man_subchoice;
    switch (man_subchoice)
    {
    case 1:
        cout << "Customers List is given below:- " << endl;
        for (unsigned int i = 0; i < customers.size(); i++)
        {
            cout << 1 + i << ". ";
            customers[i].show_short_detail();
            cout << "\n -------------------------------" << endl;
        }
        break;
    default:
        cout << "Invalid Input" << endl;
        break;
    }
}
void manager::hire_new_emp(vector<bank_emp> &staff)
{
    string empName;
    string empPass;
    string empDOH;
    string empPhone;
    string empEmail;
    string empdob;
    double empSalary;
    float empHike;
    cout << ".....ADD NEW EMPLOYEE....." << endl;
    // cout << "Hire an Employee....." << endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter the employee name: " << endl;
    getline(cin, empName);
    cout << "Enter the employee Phone number: " << endl;
    getline(cin, empPhone);
    cout << "Enter the employee Email: " << endl;
    getline(cin, empEmail);
    cout << "Enter employee's Date of Birth: \n";
    getline(cin, empdob);
    // cout << "Set the employee's password: " << endl;
    // getline(cin, empPass);
    cout << "Enter the employee's monthly salary: " << endl;
    cin >> empSalary;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter the salary increment per annum: " << endl;
    cin >> empHike;
    std::cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter the temporary employee pass: " << endl;
    cin >> empPass;
    std::cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    empDOH = get_date();

    // send an email to the emp_email telling him/her about the password...

    bank_emp new_emp(empName, empDOH, empPhone, empEmail, empdob, empSalary, empHike, empPass);
    staff.push_back(new_emp);
    save_employees_to_file(staff);
    cout << "=====================================================" << endl;
    cout << "Account created successfully with Employee ID: " << new_emp.get_emp_ID() << ", On date " << empDOH << endl;

    cout << "Employee hired and data saved instantly." << std::endl;
    cout << "The Employee Password is sent to employee email address." << endl;
}
/// @brief
/// @param staff
void manager::view_emp_detail(const vector<bank_emp> staff)
{
    int emp_id;
    bool emp_found = false;
    emp_id = get_valid_input<int>("Enter Employee ID to view:- ", 1, 9999);

    for (unsigned int i = 0; i < staff.size(); i++)
    {
        if (staff[i].get_emp_ID() == emp_id)
        {
            staff[i].show_emp_detail_man();
            emp_found = true;
        }
    }
    if (!emp_found)
    {
        cout << "ERROR! Employee ID not found." << endl;
    }
}
void manager::update_emp_detail(vector<bank_emp> &staff)
{
    int empID;
    // bool acc_found = false;
    bank_emp *ID_to_update = nullptr;
    empID = get_valid_input<int>("Enter Employee ID to view:- ", 1, 9999);

    for (unsigned int i = 0; i < staff.size(); i++)
    {
        if (staff[i].get_emp_ID() == empID)
        {
            staff[i].show_emp_detail_man();
            ID_to_update = &staff[i];
            // acc_found = true;
        }
    }
    if (ID_to_update != nullptr)
    {
        int choice;
        do
        {
            cout << "\nWhat would you like to update?" << endl;
            cout << "1. Employee Name" << endl;
            cout << "2. Employee Phone Number" << endl;
            cout << "3. Employee Email Address" << endl;
            cout << "4. Employee Salary" << endl;
            cout << "5. Employee Salary Increment per annum(%)" << endl;
            cout << "6. Exit Update Menu" << endl;
            choice = get_valid_input<int>("Enter your choice: ", 1, 6);

            switch (choice)
            {
            case 1:
            {
                string newName;
                cout << "Enter the new name: " << endl;
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, newName);
                (*ID_to_update).set_emp_name(newName);
                save_employees_to_file(staff);
                cout << " Name updated successfully." << endl;
                break;
            }
            case 2:
            {
                string newPhone;
                cout << "Enter the new phone: " << endl;
                getline(cin, newPhone);
                (*ID_to_update).set_emp_phone(newPhone);
                save_employees_to_file(staff);
                cout << " Phone Number updated successfully." << endl;
                break;
            }
            case 3:
            {
                string newEmail;
                cout << "Enter the new email: " << endl;
                getline(cin, newEmail);
                (*ID_to_update).set_emp_email(newEmail);
                save_employees_to_file(staff);
                cout << " Email updated successfully." << endl;
                break;
            }
            case 4:
            {
                double newSalary;
                cout << "Enter the new salary: " << endl;
                cin >> newSalary;
                (*ID_to_update).set_emp_salary(newSalary);
                save_employees_to_file(staff);
                cout << " Salary updated successfully." << endl;
                break;
            }
            case 5:
            {
                float new_increment;
                cout << "Enter the new Increment percentage: " << endl;
                cin >> new_increment;
                (*ID_to_update).set_emp_hike(new_increment);
                save_employees_to_file(staff);
                cout << " Hike percentage updated successfully." << endl;
                break;
            }
            case 6:
            {
                cout << "Exiting Update Menu..." << endl;
                break;
            }
            default:
                cout << "ERROR! Invalid Input" << endl;
                break;
            }
        } while (choice != 6);
    }
    else
    {
        {
            cout << "ERROR! Employee ID not found." << endl;
        }
    }
}
void manager::fire_emp(vector<bank_emp> &staff)
{
    int emp_id;
    int index_to_fire = -1; // Use -1 to indicate no employee found

    emp_id = get_valid_input<int>("Enter Employee ID to view:- ", 1, 9999);

    // 2. Search Loop (Find and Confirm)
    for (unsigned int i = 0; i < staff.size(); i++)
    {
        if (staff[i].get_emp_ID() == emp_id)
        {
            staff[i].show_emp_detail_man(); // Show details for confirmation
            index_to_fire = i;              // Store the correct index
            break;                          // Stop searching immediately
        }
    }

    // 3. Deletion and Confirmation Flow
    if (index_to_fire != -1)
    { // Employee was found
        int man_choice;
        cout << "\nAre you sure you want to FIRE employee " << emp_id << "?" << endl;
        cout << "Enter: \n 1. FIRE \n 2. CANCEL" << endl;
        cin >> man_choice;

        if (man_choice == 1)
        {
            // CRITICAL FIX: Erase using the stored, correct index
            staff.erase(staff.begin() + index_to_fire);

            // Save immediately for real-time persistence
            save_employees_to_file(staff);

            cout << "Employee " << emp_id << " fired successfully and data saved." << endl;
        }
        else
        {
            cout << "Termination cancelled. Returning to menu." << endl;
        }
    }
    else
    {
        // Employee was not found
        cout << "ERROR! Employee ID " << emp_id << " not found." << endl;
    }
}
void manager::view_all_emps(const vector<bank_emp> staff)
{
    int total_employees = staff.size();
    if (staff.empty())
    {
        cout << "No employee data available yet." << endl;
    }
    int man_subchoice;
    cout << "\n Total Employees = " << total_employees << endl;

    if (!staff.empty())
    {
        cout << "Press 1 to see the full employees list." << endl;
        cin >> man_subchoice;
        switch (man_subchoice)
        {
        case 1:
            cout << "Employees List is given below:- " << endl;
            for (unsigned int i = 0; i < staff.size(); i++)
            {
                cout << 1 + i << ". ";
                staff[i].show_short_detail();
                cout << "\n-------------------------------" << endl;
            }
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
        }
    }
    else
    {
        cout << "  No Employee data found." << endl;
    }
}
void manager::view_balancesheet()
{
    cout << "Balance Sheet" << endl;
}
void manager::load_data( vector<bank_emp> staff, vector<bank_account> customers, vector<acc_close_request> &requests){
    load_closure_requests(requests);
    load_customers(customers);
    load_employees(staff);
}
