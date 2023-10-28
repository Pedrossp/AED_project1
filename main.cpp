#include "Lesson.h"
#include "Student.h"
#include "UC_Class.h"
#include "DataManip.h"

#include <iostream>

using namespace std;

int main(){
    DataManip data;
    data.read_classes_per_uc("schedule/classes_per_uc.csv");
    vector<UC_Class*> uc = data.get_uc_classes();
    for(UC_Class* a: uc){
        cout << a->get_ucCode() << "\n";
        cout << "a";
    }

    return 0;

}