#ifndef AED_PROJECT_STUDENTS_H
#define AED_PROJECT_STUDENTS_H
#include <string>
#include <vector>

using namespace std;

class Student {
private:
    string StudentName;
    string StudentCode;
    vector<pair<UC, Class>> UC_Class;


public:
    Student(string& StudentName, string& StudentCode, vector& <pair<UC, Class>> UC_Class);
    string get_name();
    string get_code();

};

#endif //AED_PROJECT_STUDENTS_H<<<<<<< HEAD