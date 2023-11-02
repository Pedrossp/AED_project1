#include "Student.h"
#include "UC_Class.h"

#include <string>
#include <algorithm>

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

void Student::rem(UC_Class* uc_class) {

    auto it = remove_if(uc_Classes_.begin(), uc_Classes_.end(),[uc_class] (UC_Class* t){ return (uc_class->get_ucCode() == t->get_ucCode()) && (uc_class->get_classCode() == t->get_classCode());});
    uc_Classes_.erase(it, uc_Classes_.end());

}

