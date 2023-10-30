#include "Lesson.h"
#include "DataManip.h"
#include "UC_Class.h"
#include "Student.h"
#include "Test.h"

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    DataManip data;
    data.read_classes_per_uc("../schedule/classes_per_uc.csv");
    data.read_classes("../schedule/classes.csv");
    vector<UC_Class *> uc = data.get_uc_classes();

    for (UC_Class *a : uc) {
        std::cout << a->get_ucCode() << " " << a->get_classCode() << "\n";

        vector<Lesson*> ls = a->get_lessons();
        if (ls.empty()) {
            cout << "Sem aulas para esta classe.\n";
        } else {
            for (Lesson *b : ls) {
                cout << b->get_duration() << " " << b->get_starthour() << " " << b->get_type() << " " << b->get_weekday() << endl;
            }
        }
    }

    return 0;
}
    /*
    UC_Class* y = new UC_Class("L.EIC001","1LEIC20");
    UC_Class *x = data.found_ucclass(y);
    cout<< x-> get_ucCode() <<" " <<x->get_classCode();
    //Student *x = data.found_student(202025487);
    //cout << x->get_code();

    Test *test = new Test();
    test->test1();
    return 0;
}
     */