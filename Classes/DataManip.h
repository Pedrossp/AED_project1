#ifndef AED_PROJECT1_DATAMANIP_H
#define AED_PROJECT1_DATAMANIP_H

#include <queue>

#include "Student.h"
#include "string"
#include "UC_Class.h"
#include "Student.h"
#include "DataManip.h"
#include "Request.h"

using namespace std;


class DataManip {

private:
    vector<UC_Class*> uc_classes_;
    vector<Student*> students_;
    queue<Request*> pendent_requests_;
    queue<Request*> denied_requests_;

public:

    void read_classes(string filename);
    void read_classes_per_uc(string filename);
    void read_students_classes(string filename);

    vector<UC_Class*> get_uc_classes();
    vector<Student*> get_students();
    queue<Request*> get_pendent_requests();
    queue<Request*> get_denied_request();

    void sortStudents_bycode(vector<Student*>);

    Student* found_student(int student_code);
    UC_Class* found_ucclass(string uc_code, string class_code);

    void set_pendent_requests(Request* request);
    void set_denied_request(Request* request);

    bool switch_class(int student_code, UC_Class uc_class);
    bool join_new_ucClass(int student_code, UC_Class uc_class);
    void leave_ucClass(int student_code, UC_Class uc_class);

};


#endif //AED_PROJECT1_DATAMANIP_H
