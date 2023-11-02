#ifndef AED_PROJECT_STUDENTS_H
#define AED_PROJECT_STUDENTS_H

#include "UC_Class.h"

#include <string>
#include <vector>

using namespace std;


class Student {
private:
    string studentName_;
    int studentCode_;
    vector<UC_Class*> uc_Classes_;


public:
    Student();
    Student(string& studentName, int studentCode);

    string const get_name();
    int const get_code();
    vector<UC_Class*> const get_uc_classes();

    void rem(UC_Class* uc_class);

    void set_uc_class(UC_Class* uc_Classes);

};

#endif //AED_PROJECT_STUDENTS_H<<<<<<< HEAD