#include "Lesson.h"
#include "DataManip.h"
#include "UC_Class.h"
#include "Student.h"

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    DataManip data;
    data.read_classes_per_uc("../schedule/classes.csv");
    data.read_students_classes("../schedule/test.txt");
    vector<UC_Class *> uc = data.get_uc_classes();
    vector<Student*> students= data.get_students();

    for (UC_Class*a : uc) {

        std::cout<<a->get_ucCode() <<" "<<a->get_classCode()<<"\n";

    }
    UC_Class* y = new UC_Class("L.EIC001","1LEIC20");
    UC_Class *x = data.found_ucclass(y);
    cout<< x-> get_ucCode() <<" " <<x->get_classCode();
    //Student *x = data.found_student(202025487);
    //cout << x->get_code();
    return 0;
}