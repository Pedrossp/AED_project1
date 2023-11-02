#include "Request.h"

Request::Request(Student student, UC_Class uc_class, string type) {
    student_ = student;
    uc_class_ = uc_class;
    type_ = type;
}

Student Request::get_student() {
    return student_;
}

UC_Class Request::get_ucClass() {
    return uc_class_;
}

string Request::get_type() {
    return type_;
}
