#include "Lesson.h"
#include "DataManip.h"
#include "UC_Class.h"
#include "Student.h"
#include "Test.h"
#include "Menu.h"

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    /*
    DataManip data;
    data.read_classes_per_uc("../schedule/classes_per_uc.csv");
    data.read_classes("../schedule/classes.csv");
    data.read_students_classes("../schedule/students_classes.csv");
    Test *test = new Test(data);
    */

    //test->test_read_student_classes();

    //test->test1();

    //test->test_read_classes();

    //test->test_consultStudentSchedule();

    //test->test_consultClassSchedule();

    //test->test_consultStudentClass();

    //test->test_consultStudentUc();

    //test->test_consultStudentYear();

    //test->test_consultStudentsEnrolled();

    //test->test_consultClassOcupation();

    //test->test_consultMaxUc();

    //test->test_leave_ucClass();

    //test->test_classCode_student();

    //test->test_join_new_ucClass();

    DataManip data;
    Menu menu(data);
    menu.run();

    return 0;
}

