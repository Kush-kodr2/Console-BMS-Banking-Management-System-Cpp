#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <fstream>
#include <vector>
using namespace std;
class bank_account;
class bank_emp;

void save_customers_to_file(const vector<bank_account> &customers, const string &filename = "data/customer_data.csv");
void save_employees_to_file(const vector<bank_emp> &employees, const string &filename = "data/employee_data.csv");

void load_customers(vector<bank_account> &customers,const string &filename = "data/customer_data.csv");
void load_employees(vector<bank_emp> &employees,const string &filename = "data/employee_data.csv");

#endif