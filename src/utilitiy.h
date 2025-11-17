#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <limits>
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

#endif