#include "Request.h"

Request::Request(Student student, string uc_code, string class_code, string type) {
    student_ = student;
    uc_code_ = uc_code;
    class_code_ = class_code;
    type_ = type;
}

Student Request::get_student() {
    return student_;
}

string Request::get_uc_code() {
    return uc_code_;
}

string Request::get_class_code() {
    return class_code_;
}

string Request::get_type() {
    return type_;
}
