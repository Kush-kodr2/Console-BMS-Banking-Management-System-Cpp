#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <vector>
#include<string>

using namespace std;
string get_date();
class bank_account
{
private:
    static int nextAccountNumber;
    string holder_name;
    int acc_num;
    double balance;
    string date_of_birth;
    string email_add;
    int user_pass;
    int acc_type;

public:
    bank_account(string holderName, double initBalance, string email_id, string dob, int acc_typ, int pin)
    {
        holder_name = holderName;
        balance = initBalance;
        email_add = email_id;
        date_of_birth = dob;
        acc_type = acc_typ;
        acc_num = nextAccountNumber++;
        user_pass = pin;
    }
    bool cst_login(const int);
    void deposit_money(double);
    void withdraw_money(double);
    void display_balance() const;
    void show_acc_details() const;
    void show_short_detail() const;
    void terms_conditions();
    void setName(string);
    void setEmail(string);
    void setDob(string);
    void setAccType(int);
    int getaccnum() const
    {
        return acc_num;
    }
};

class Acc_Close_Request
{
public:
    int acc_num;
    int employee_ID;
    string employee_Name;

    Acc_Close_Request(int acc, const int empID, const string &empName)
        : acc_num(acc), employee_ID(empID), employee_Name(empName) // initializer list new feature in cpp, used instead of the old constructor body assignment, as given below.
    {
        // acc_num = accNum;
        // employee_ID = empID;
    }
};

class bank_emp
{
private:
    static int next_emp_ID;
    int emp_ID;
    string emp_pass;
    string emp_name;
    string date_of_hire;
    string emp_phone_num;
    string emp_email;
    double monthly_salary;
    float increment_pa;

public:
    bool login(const int, const string);
    void open_new_acc(vector<bank_account> &customers);
    void update_acc_info(vector<bank_account> &customers);
    void view_acc(const vector<bank_account> &customers);
    void close_acc(vector<bank_account> &customers, vector<Acc_Close_Request> &requests);
    bank_emp(string name, string pass, string doh, string phone, string email, double mon_salary, float incre_pa) : emp_ID(next_emp_ID++), emp_name(name), emp_pass(pass), date_of_hire(doh), emp_phone_num(phone), emp_email(email), monthly_salary(mon_salary), increment_pa(incre_pa)
    {
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
};

class manager
{
private:
    int manager_ID;
    string manager_pass;
    string manager_PIN;

public:
    void open_new_acc(vector<bank_account> &customers);
    void view_acc(const vector<bank_account> &customers);
    void close_acc(vector<bank_account> &customers, vector<Acc_Close_Request> &requests);

    void hire_new_emp(vector<bank_emp> &staff);
    void view_emp_detail(const vector<bank_emp> staff);
    void update_emp_detail(vector<bank_emp> &staff);
    void fire_emp(vector<bank_emp> &staff);

    void view_all_emps(const vector<bank_emp> staff);
    void view_all_customers(const vector<bank_account> customers);
    void view_balancesheet();
    bool check_credentials(const int, const string &);

    manager(int, string);
};


#endif