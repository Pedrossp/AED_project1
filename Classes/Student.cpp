#include "Student.h"
#include "UC_Class.h"

#include <string>

using namespace std;


Student::Student(){
    studentName_ = "";
    studentCode_ = 0;
}

Student::Student(string& studentName, int studentCode){
    studentName_ = studentName;
    studentCode_ = studentCode;
}

string const Student::get_name(){
    return studentName_;
}

int const Student::get_code(){
    return studentCode_;
}

vector<UC_Class*> const Student::get_uc_classes(){
    return uc_Classes_;
}

void Student::set_uc_class(UC_Class* uc_Classes){
    uc_Classes_.push_back(uc_Classes);
}


