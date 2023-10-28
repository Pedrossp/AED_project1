#ifndef AED_PROJECT1_DATAMANIP_H
#define AED_PROJECT1_DATAMANIP_H

#include "Student.h"
#include "string"

using namespace std;


class DataManip {

private:
    vector<UC_Class*> uc_classes_;

public:
    void read_classes(string filename);
    void read_classes_per_uc(string filename);
    void read_students_classes(string filename);

    vector<UC_Class*> get_uc_classes();

};


#endif //AED_PROJECT1_DATAMANIP_H
