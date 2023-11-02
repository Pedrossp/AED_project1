#ifndef AED_PROJECT1_TEST_H
#define AED_PROJECT1_TEST_H

#include "DataManip.h"

class Test {

private:
    DataManip data_;

public:
    Test(DataManip data);

    void test1();
    void test_read_classes();
    void test_read_student_classes();
    void test_consultStudentSchedule();
    void test_consultClassSchedule();
    void test_consultStudentClass();
    void test_consultStudentUc();
    void test_consultStudentYear();
    void test_consultStudentsEnrolled();
    void test_consultClassOcupation();
    void test_consultMaxUc();
    void test_leave_ucClass();
};


#endif //AED_PROJECT1_TEST_H
