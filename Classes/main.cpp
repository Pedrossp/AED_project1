#include "Lesson.h"
#include "DataManip.h"
#include "UC_Class.h"
#include "Student.h"
#include "Test.h"

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    /*
    Test *test = new Test();
    test->test_read_student_classes();
    */


    /*
    Test *test = new Test();
    test->test1();
     */


    Test *test = new Test();
    test->test_read_classes();

    return 0;
}

