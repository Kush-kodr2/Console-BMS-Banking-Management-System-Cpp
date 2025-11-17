#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

template <typename T>
T get_valid_input(const string &prompt, T min_val, T max_val)
{
    T value;
    bool is_valid = false;
    do
    {
        cout << prompt;
        if (!(cin >> value))
        {
            cout << "\nInvalid input! Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (cin.peek() != '\n' && cin.peek() != EOF)
        {
            cout << "\nINVALID INPUT! Please enter only a number, no extra characters." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (value < min_val)
        {
            cout << "\nINVALID INPUT! Value can't be smaller than " << min_val<<endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (value > max_val)
        {
            cout << "\nINVALID INPUT! Value can't be greater than " << max_val<<endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            // All checks passed!
            is_valid = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!is_valid);

    return value;
}

 
// trim function

inline string trim(string s) {
    // Defines all characters considered whitespace: space, tab, carriage return, newline
    const string whitespace = " \t\r\n";
    
    // 1. Find the position of the first character that IS NOT whitespace
    size_t start = s.find_first_not_of(whitespace);
    
    // If the entire string is whitespace (start == string::npos), return an empty string
    if (start == std::string::npos) 
        return std::string();
    
    // 2. Find the position of the last character that IS NOT whitespace
    size_t end = s.find_last_not_of(whitespace);
    
    // 3. Extract the clean substring
    // The length of the substring is calculated as (end - start + 1)
    return s.substr(start, end - start + 1);
};
#endif