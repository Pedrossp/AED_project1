#include "Lesson.h"
#include "Student.h"
#include "UC_Class.h"
#include "DataManip.h"

#include <iostream>

using namespace std;

int main() {
    DataManip data;
    data.read_classes_per_uc("home/edu/Feup/AED/AED_PROJECT/schedule/classes_per_uc.csv"
    );
    std::vector<UC_Class *> uc = data.get_uc_classes();
    for (UC_Class *a : uc) {
        std::cout << a->get_ucCode();
    }

    return 0;
}