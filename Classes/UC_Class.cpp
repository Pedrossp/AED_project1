#include "UC_Class.h"

UC_Class::UC_Class() {
    UcCode_ = "";
    ClassCode_ = "";
}

UC_Class::UC_Class(std::string UcCode, std::string ClassCode) {
    UcCode_ = UcCode;
    ClassCode_ = ClassCode;
}

const string UC_Class::get_ucCode() {
    return UcCode_;
}

const string UC_Class::get_classCode() {
    return ClassCode_;
}

const vector<Lesson *> UC_Class::get_lessons() {
    return Lessons_;
}

void UC_Class::set_lessons(Lesson* Lessons) {
    Lessons_.push_back(Lessons);
}

