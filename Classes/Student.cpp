#include "Student.h"

using namespace std;

Student::Student(string& StudentName, string& StudentCode, vector& <pair<UC, Class>> UC_Class){
    StudentName_ = StudentName;
    StudentCode_ = StudentCode;
    UC_Class_ = UC_Class;
}

string Student::get_name() {
    return StudentName_;
}

string Student::get_code() {
    return StudentCode_;
}
