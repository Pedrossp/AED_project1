#ifndef AED_PROJECT_STUDENTS_H
#define AED_PROJECT_STUDENTS_H
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Students {
private:
    string StudentName;
    string StudentCode;
    vector<pair<UC, Class>> UC_Class;


public:
    Students(string &StudentName, int StudentCode, vector & <pair<UC, Class>> UC_Class);
    string&get_name();
    string& get_code();
};

#endif //AED_PROJECT_STUDENTS_H<<<<<<< HEAD