#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <fstream>
#include <vector>
using namespace std;
class close_acc_requests;
class bank_account;
class bank_emp;

void save_customers_to_file(const vector<bank_account> &customers, const string &filename = "data/customer_data.csv");
void save_employees_to_file(const vector<bank_emp> &employees, const string &filename = "data/employee_data.csv");

void load_customers(vector<bank_account> &customers, const string &filename = "data/customer_data.csv");
void load_employees(vector<bank_emp> &employees, const string &filename = "data/employee_data.csv");

void save_closure_requests(const vector<acc_close_request> &requests, const string &filename = "data/closure_requests.csv");
void load_closure_requests(vector<acc_close_request> &requests, const string &filename = "data/closure_requests.csv");

void load_managers(vector<manager>& managers, const string& filename = "data/manager_config.csv");
#endif