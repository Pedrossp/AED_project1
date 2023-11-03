#ifndef AED_PROJECT1_REQUEST_H
#define AED_PROJECT1_REQUEST_H

#include "Student.h"

class Request {

private:
    Student student_;
    string uc_code_;
    string class_code_;
    string type_;

public:
    Request(Student student, string uc_code ,string class_code, string type);
    Student get_student();
    string get_uc_code();
    string get_class_code();
    string get_type();

};


#endif //AED_PROJECT1_REQUEST_H
