#include "definitions.h"
#include "utilitiy.h"
#include "data_handler.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept> // For exception in catch, in ifstream
using namespace std;

void save_customers_to_file(const vector<bank_account> &customers, const string &filename)
{
    ofstream customers_write(filename);
    if (!customers_write.is_open())
    {
        cerr << "Could not open " << filename << " for saving customer data!" << endl;
        return;
    }
    for (unsigned int i = 0; i < customers.size(); i++)
    {
        customers_write << customers[i].getaccnum() << ","
                        << customers[i].get_account_type() << ","
                        << customers[i].get_cust_name() << ","
                        << customers[i].get_balance() << ","
                        << customers[i].get_dob() << ","
                        << customers[i].get_email() << ","
                        << customers[i].get_pass()
                        << endl;
    }
}
void save_employees_to_file(const vector<bank_emp> &employees, const string &filename)
{
    ofstream employees_write(filename);

    if (!employees_write.is_open())
    {
        cerr << "ERROR: Could not open " << filename << " for saving employee data! " << endl;
        return;
    }

    for (unsigned int i = 0; i < employees.size(); i++)
    {
        employees_write << employees[i].get_emp_ID() << ","
                        << employees[i].get_date_of_hire() << ","
                        << employees[i].get_emp_name() << ","
                        << employees[i].get_salary() << ","
                        << employees[i].get_sal_incre() << ","
                        << employees[i].get_emp_dob() << ","
                        << employees[i].get_emp_email() << ","
                        << employees[i].get_emp_phone() << ","
                        << employees[i].get_emp_pass() << ","
                        << employees[i].get_not_changed_pass() << endl;
    }
}

void load_customers(vector<bank_account> &customers, const string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "[System] Customer data file not found (" << filename << "). " << endl;
        return;
    }
    cout << "[DEBUG] File opened successfully." << endl;
    auto is_valid_int = [](const string &s)
    {
        if (s.empty())
            return false;
        for (size_t i = 0; i < s.length(); ++i)
        {
            char c = s[i];
            if (!isdigit(c) && c != '-')
            {
                return false;
            }
        }
        return true;
    };
    auto is_valid_double = [](string &s)
    {
        if (s.empty())
        {
            return false;
        }
        bool dot_found = false;

        for (size_t i = 0; i < s.length(); ++i)
        {
            char c = s[i];

            if (c == '.')
            {
                if (dot_found)
                {
                    return false;
                }
                dot_found = true;
            }
            else if (!isdigit(c) && c != '-')
            {
                return false;
            }
        }
        return true;
    };
    auto trim = [](string s) -> string
    {
        const string whites = " \t\r\n";
        size_t start = s.find_first_not_of(whites);
        if (start == string::npos)
            return string();
        size_t end = s.find_last_not_of(whites);
        return s.substr(start, end - start + 1);
    };
    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue; // for skipping the blank lines, not necessary
        }
        stringstream ss(line);
        string segment;

        string user_name, user_pass, user_email, user_dob, user_acc_type;
        int user_acc_num = 0;
        double user_bal = 0.0;

        int fieldIndex = 0;
        bool skip_line = false;

        while (getline(ss, segment, ','))
        {
            segment = trim(segment);
            try
            {
                if (fieldIndex == 0)
                {
                    if (!is_valid_int(segment))
                    {
                        throw invalid_argument("Invalid accNum");
                    }
                    user_acc_num = stoi(segment);
                }
                else if (fieldIndex == 1)
                {
                    user_acc_type = segment;
                }
                else if (fieldIndex == 2)
                {
                    user_name = segment;
                }
                else if (fieldIndex == 3)
                {
                    if (!is_valid_double(segment))
                    {
                        throw invalid_argument("Invalid balance");
                    }
                    user_bal = stod(segment);
                }
                else if (fieldIndex == 4)
                {
                    user_dob = segment;
                }
                else if (fieldIndex == 5)
                {
                    user_email = segment;
                }
                else if (fieldIndex == 6)
                {
                    user_pass = segment;
                }
                fieldIndex++;
            }

            catch (const exception &e)
            {
                cerr << "\n[ERROR] Skipping corrupted customer record: " << line << " Reason: " << e.what() << endl;
                skip_line = true;
                break;
            }
        }
        if (skip_line || fieldIndex < 4)
        {
            continue;
        }

        // Require at least 7 fields (accnum, acc_type, name, balance, dob, email, pass)
        if (skip_line || fieldIndex < 7)
        {
            // skip malformed/partial entries
            continue;
        }

        // Create account preserving the original account number
        bank_account loaded_acc(user_name, user_bal, user_email, user_dob, user_acc_type, user_pass, user_acc_num);
        customers.push_back(loaded_acc);
    }
    file.close();
    cout << "[System] Customer data loaded successfully." << endl;
}
void load_employees(vector<bank_emp> &employees, const string &filename)
{
    ifstream emp_file(filename);

    if (!emp_file.is_open())
    {
        cerr << "[System] Employee data file not found. " << filename << endl;
        return;
    }
    auto is_valid_int = [](const string &s)
    {
        if (s.empty())
            return false;
        for (size_t i = 0; i < s.length(); ++i)
        {
            char c = s[i];
            if (!isdigit(c) && c != '-')
            {
                return false;
            }
        }
        return true;
    };
    auto is_valid_double = [](string &s)
    {
        if (s.empty())
        {
            return false;
        }
        bool dot_found = false;

        for (size_t i = 0; i < s.length(); ++i)
        {
            char c = s[i];

            if (c == '.')
            {
                if (dot_found)
                {
                    return false;
                }
                dot_found = true;
            }
            else if (!isdigit(c) && c != '-')
            {
                return false;
            }
        }
        return true;
    };
    auto trim = [](string s) -> string
    {
        const string whites = " \t\r\n";
        size_t start = s.find_first_not_of(whites);
        if (start == string::npos)
            return string();
        size_t end = s.find_last_not_of(whites);
        return s.substr(start, end - start + 1);
    };
    string line;

    while (getline(emp_file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string segment;

        string emp_name, emp_phone, emp_email, emp_doh, emp_dob;
        int emp_id = 0;
        double emp_salary = 0;
        float emp_sal_incr = 0.0;
        string emp_pass;
        int field_index = 0;
        bool skip_line = false;
        bool not_changed_pass;
        while (getline(ss, segment, ','))
        {
            try
            {
                if (field_index == 0)
                {
                    if (!is_valid_int(segment))
                        throw invalid_argument("Invalid emp_id");
                    emp_id = stoi(segment);
                }
                else if (field_index == 1)
                {
                    emp_doh = segment;
                }
                else if (field_index == 2)
                {
                    emp_name = segment;
                }
                else if (field_index == 3)
                {
                    if (!is_valid_double(segment))
                    {
                        throw invalid_argument("Invalid salary");
                    }
                    emp_salary = stod(segment);
                }
                else if (field_index == 4)
                {
                    if (!is_valid_double(segment))
                    {
                        throw invalid_argument("Invalid salary increment");
                    }
                    emp_sal_incr = stof(segment);
                }
                else if (field_index == 5)
                {
                    emp_dob = segment;
                }
                else if (field_index == 6)
                {
                    emp_email = segment;
                }
                else if (field_index == 7)
                {
                    emp_phone = segment;
                }
                else if (field_index == 8)
                {
                    emp_pass = segment;
                }
                else if (field_index == 9)
                {
                    segment = trim(segment);
                    if (!is_valid_int(segment))
                    {
                        throw invalid_argument("Invalid Flag");
                    }
                    not_changed_pass = stoi(segment);
                }

                field_index++;
            }
            catch (const exception &e)
            {
                cerr << "\n[ERROR] Skipping corrupted employee record: " << line << " Reason: " << e.what() << endl;
                skip_line = true;
                break;
            }
        }
        if (skip_line)
        {
            continue;
        }
        bool final_not_changed = (not_changed_pass == 1);
        bank_emp loaded_emp(emp_id, emp_pass, emp_name, emp_doh, emp_phone, emp_email, emp_dob, emp_salary, emp_sal_incr, final_not_changed);
        employees.push_back(loaded_emp);
    }
    emp_file.close();
    cout << "[System] Employee data loaded successfully." << endl;
}

void save_closure_requests(const vector<acc_close_request> &requests, const string &filename)
{
    ofstream write_reqs(filename, ios::trunc);
    if (!write_reqs.is_open())
    {
        cerr << "Could not open " << filename << " for saving account closure requests!" << endl;
        return;
    }
    for (unsigned int i = 0; i < requests.size(); i++)
    {
        write_reqs << requests[i].get_acc_num() << ","
                   << requests[i].get_emp_ID() << ","
                   << requests[i].get_emp_name() << endl;
    }
}
void load_closure_requests(vector<acc_close_request> &requests, const string &filename)
{
    ifstream read_reqs(filename);
    if (!read_reqs.is_open())
    {
        cerr << "[System] Closure Requests data file not found. " << filename << endl;
        return;
    }
    string line;
    while (getline(read_reqs, line))
    {
        if (line.empty())
        {
            continue;
        }
        stringstream ss(line);
        string acc_num_str, empID_str, emp_name;

        getline(ss, acc_num_str, ',');
        getline(ss, empID_str, ',');
        getline(ss, emp_name);
        try
        {
            int acc_num = stoi(acc_num_str);
            int emp_id = stoi(empID_str);

            acc_close_request loaded_request(acc_num, emp_id, emp_name);
            requests.push_back(loaded_request);
        }
        catch (const exception &e)
        {
            cerr << "[Error] Skipping corrupted request record." << endl;
        }
    }
}

void save_managers(const vector<manager> &managers, const string &filename)
{
    ofstream write_pass(filename);
    if (!write_pass.is_open())
    {
        cerr << "Could not open " << filename << " for saving manager data!" << endl;
        return;
    }
    for (unsigned int i = 0; i < managers.size(); i++)
    {
        write_pass << managers[i].get_man_id() << ","
                   << managers[i].get_man_pass() << ","
                   << (managers[i].get_not_changed_pass() ? 1 : 0) << endl;
    }
}
void load_managers(vector<manager> &managers, const string &filename)
{

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "[System] Manager config file not found. Starting with empty manager list." << std::endl;
        return;
    }

    string line;
    auto trim_local = [](string s) -> string
    {
        const string whites = " \t\r\n";
        size_t start = s.find_first_not_of(whites);
        if (start == string::npos)
            return string();
        size_t end = s.find_last_not_of(whites);
        return s.substr(start, end - start + 1);
    };

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string idStr, passStr, flagStr;
        bool not_changed_pass = false;

        if (!getline(ss, idStr, ','))
            continue;
        if (!getline(ss, passStr, ','))
        {
            // if only one field present, skip
            continue;
        }
        // optional flag: if present read remaining token
        if (!getline(ss, flagStr))
        {
            flagStr = "0"; // default: not changed = false
        }

        passStr = trim_local(passStr);
        idStr = trim_local(idStr);
        flagStr = trim_local(flagStr);

        try
        {
            not_changed_pass = (stoi(flagStr) == 1);
            // Create the Manager object using the data from the file
            manager loadedManager(idStr, passStr, not_changed_pass);
            managers.push_back(loadedManager);
        }
        catch (const exception &e)
        {
            cerr << "[Error] Skipping corrupted manager record: " << line << std::endl;
        }
    }

    file.close();
    cout << "[System] Manager credentials loaded successfully." << std::endl;
}