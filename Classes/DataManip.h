#ifndef AED_PROJECT1_DATAMANIP_H
#define AED_PROJECT1_DATAMANIP_H

#include "Classes/Student.h"
#include "string"
#include "Classes/UC_Class.h"
#include "Classes/Student.h"

using namespace std;


class DataManip {

private:
    vector<UC_Class*> uc_classes_;
    vector<Student*> students_;

public:
    void read_classes(string filename);
    void read_classes_per_uc(string filename);
    void read_students_classes(string filename);

    vector<UC_Class*> get_uc_classes();
    vector<Student*> get_students();

    void sortStudents_bycode(vector<Student*>);
};


#endif //AED_PROJECT1_DATAMANIP_H
