#ifndef AED_PROJECT1_REQUEST_H
#define AED_PROJECT1_REQUEST_H

#include "Student.h"

class Request {

private:
    Student student_;
    UC_Class uc_class_;
    string type_;

public:
    Request(Student student, UC_Class uc_class, string type);
    Student get_student();
    UC_Class get_ucClass();
    string get_type();

};


#endif //AED_PROJECT1_REQUEST_H
