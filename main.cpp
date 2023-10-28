#include "Lesson.h"
#include "Student.h"
#include "UC_Class.h"
#include "DataManip.h"

#include <iostream>

using namespace std;

int main() {
    DataManip data;
    data.read_classes_per_uc("../schedule/classes.csv");
    std::vector<UC_Class *> uc = data.get_uc_classes();

    for (UC_Class *a : uc) {
        std::cout << a->get_ucCode()<<" "<<a->get_classCode()<<"\n";

    }
    return 0;
}