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
    data.read_students_classes("../schedule/students_classes.csv");
    vector<UC_Class *> uc = data.get_uc_classes();
    vector<Student*> students= data.get_students();

    for (Student *a : students) {

        std::cout <<a->get_code()<<"\n";

    }
    return 0;
}