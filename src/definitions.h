#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <vector>
#include <string>

using namespace std;
class bank_account
{
private:
    static int nextAccountNumber;
    string holder_name;
    int acc_num;
    double balance;
    string date_of_birth;
    string email_add;
    string user_pass;
    string acc_type;

public:
    bank_account(string holderName, double initBalance, string email_id, string dob, string acc_typ, string pin)
    {
        holder_name = holderName;
        balance = initBalance;
        email_add = email_id;
        date_of_birth = dob;
        acc_type = acc_typ;
        acc_num = nextAccountNumber++;
        user_pass = pin;
    }
    // Construct a bank account using an existing account number (used when loading from storage)
    bank_account(string holderName, double initBalance, string email_id, string dob, string acc_typ, string pin, int accountNumber): holder_name(holderName), balance(initBalance), email_add(email_id), date_of_birth(dob), acc_type(acc_typ), acc_num(accountNumber), user_pass(pin)
    {
        // Ensure nextAccountNumber stays ahead of any loaded account numbers to avoid duplicates
        if (accountNumber >= nextAccountNumber)
        {
            nextAccountNumber = accountNumber + 1;
        }
    }
    bool cst_login(const int, const string);
    void deposit_money(double);
    void withdraw_money(double);
    void display_balance() const;
    void show_acc_details() const;
    void show_short_detail() const;
    void terms_conditions();
    void setName(string);
    void setEmail(string);
    void setDob(string);
    void setAccType(string);
    int getaccnum() const
    {
        return acc_num;
    }
    double get_balance() const
    {
        return balance;
    }
    string get_cust_name() const
    {
        return holder_name;
    }
    string get_account_type() const
    {
        return acc_type;
    }
    string get_dob() const
    {
        return date_of_birth;
    }
    string get_email() const
    {
        return email_add;
    }
    string get_pass() const
    {
        return user_pass;
    }
};

class acc_close_request
{
    int acc_num;
    int employee_ID;
    string employee_Name;

public:
    acc_close_request(int acc, const int empID, const string &empName)
        : acc_num(acc), employee_ID(empID), employee_Name(empName) // initializer list new feature in cpp, used instead of the old constructor body assignment, as given below.
    {
        // acc_num = accNum;
        // employee_ID = empID;
    }
    int get_acc_num() const
    {
        return acc_num;
    }
    int get_emp_ID() const
    {
        return employee_ID;
    }
    string get_emp_name() const
    {
        return employee_Name;
    }
};

class bank_emp
{
protected:
    static int next_emp_ID;
    int emp_ID;
    string emp_pass;
    string emp_name;
    string date_of_hire;
    string emp_phone_num;
    string emp_email;
    string emp_dob;
    double monthly_salary;
    float increment_pa;
    bool not_changed_pass;
    void set_pass(const string &new_pass)
    {
        emp_pass = new_pass;
        not_changed_pass = false;
    }

public:
    bool get_not_changed_pass() const
    {
        return not_changed_pass;
    }
    void initiate_pass_change();
    bool login(const int, const string);
    void open_new_acc(vector<bank_account> &customers);
    void update_acc_info(vector<bank_account> &customers);
    void view_acc(const vector<bank_account> &customers);
    void close_acc(vector<bank_account> &customers, vector<acc_close_request> &requests);
    bank_emp(string name, string doh, string phone, string email, string dob, double mon_salary, float incre_pa, string pass) : emp_ID(next_emp_ID++), emp_name(name), emp_pass(pass), date_of_hire(doh), emp_phone_num(phone), emp_email(email), emp_dob(dob), monthly_salary(mon_salary), increment_pa(incre_pa)
    {
        this->not_changed_pass = true;
    }
    bank_emp(int id, string pass, string name, string doh, string phone, string email, string dob, double mon_salary, float incre_pa, bool not_changed_pas) : emp_ID(id), emp_name(name), emp_pass(pass), date_of_hire(doh), emp_phone_num(phone), emp_email(email), emp_dob(dob), monthly_salary(mon_salary), increment_pa(incre_pa), not_changed_pass(not_changed_pas)
    {
        if (id >= next_emp_ID)
        {
            next_emp_ID = id + 1;
        }
    }
    void set_emp_name(string);
    void set_emp_phone(string);
    void set_emp_email(string);
    void set_emp_salary(double);
    void set_emp_hike(float);

    void show_emp_detail_man() const;
    void show_emp_detail_emp() const;
    void show_short_detail() const;
    int get_emp_ID() const
    {
        return emp_ID;
    }
    string get_emp_email() const
    {
        return emp_email;
    }
    string get_emp_phone() const
    {
        return emp_phone_num;
    }
    string get_emp_name() const
    {
        return emp_name;
    }
    string get_date_of_hire() const
    {
        return date_of_hire;
    }
    string get_emp_dob() const
    {
        return emp_dob;
    }
    double get_salary() const
    {
        return monthly_salary;
    }
    float get_sal_incre() const
    {
        return increment_pa;
    }
    string get_emp_pass() const
    {
        return emp_pass;
    }
};

class manager : public bank_emp
{
private:
    string manager_ID;
    string manager_pass;

public:
    manager(string, string, bool);
    string get_man_id() const{
        return manager_ID;
    };
    string get_man_pass() const{
        return manager_pass;
    }
     void set_man_pass(const string &p);// <-- new setter
    // void open_new_acc(vector<bank_account> &customers);
    // void view_acc(const vector<bank_account> &customers);
    void close_acc(vector<bank_account> &customers, vector<acc_close_request> &requests);
    void hire_new_emp(vector<bank_emp> &staff);
    void view_emp_detail(const vector<bank_emp> staff);
    void update_emp_detail(vector<bank_emp> &staff);
    void fire_emp(vector<bank_emp> &staff);

    void view_all_emps(const vector<bank_emp> staff);
    void view_all_customers(const vector<bank_account> customers);
    void view_balancesheet();
    bool check_credentials(const string, const string &);
    void load_data(const vector<bank_emp> staff, const vector<bank_account> customers, vector<acc_close_request> &requests);
};

#endif