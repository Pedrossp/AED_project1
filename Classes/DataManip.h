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

public:
    //read files
    void read_classes(string filename);
    void read_classes_per_uc(string filename);
    void read_students_classes(string filename);

    //getters
    vector<UC_Class*> get_uc_classes();
    vector<Student*> get_students();

    void set_pendent_requests(Request* request);

    void sortStudents_bycode(vector<Student*>);
    Student* found_student(int student_code);
    UC_Class* found_ucclass(string uc_code, string class_code);
    string found_classCode_student(string uc_code, Student *student);
    void switch_class(Student *student, string uc_code, string final_class_code);
    void join_new_ucClass(int student_code, string uc_code, string class_code);
    void leave_ucClass(Student *student, string uc_code);
    void process_pendent_requests();
    void fileWriter(string filename)const;
    bool timetable_overlap(Student *student, UC_Class *uc_class_final);
    int consultClass_UcOcupation(string uc_code, string class_code);
    void ShowPendingRequests();
    bool found_if_class_code(string class_code);
    bool found_if_uc_code(string uc_code);
};


#endif //AED_PROJECT1_DATAMANIP_H
