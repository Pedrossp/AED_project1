//
// Created by edu on 30-10-2023.
//

#include <iostream>
#include "Test.h"
#include "DataManip.h"

Test::Test() {
    x_= 0;
}
void Test::test1() {
    DataManip data;
    data.read_classes_per_uc("../schedule/classes_per_uc.csv");
    vector<UC_Class *> uc = data.get_uc_classes();

    for (UC_Class*a : uc) {

        cout<<a->get_ucCode() <<" " <<a->get_classCode()<<"\n";

    }
}

void Test::test_read_student_classes() {
    DataManip data;
    data.read_classes_per_uc("../schedule/classes_per_uc.csv");
    data.read_classes("../schedule/classes.csv");
    data.read_students_classes("../schedule/students_classes.csv");

    vector<Student *> students =data.get_students();

    for(Student *student: students){

        cout << student->get_name() << ": "<< student->get_code() << "\n";

        vector<UC_Class *> uccs = student->get_uc_classes();

        for(UC_Class *ucc: uccs){

            cout << ucc->get_classCode() << ", " << ucc->get_ucCode() << "\n";
        }
    }
}

void Test::test_read_classes() {
    DataManip data;
    data.read_classes_per_uc("../schedule/classes_per_uc.csv");
    data.read_classes("../schedule/classes.csv");

    vector<UC_Class *> uc_classes =data.get_uc_classes();

    for(UC_Class * ucClass: uc_classes){

        cout << ucClass->get_ucCode() << " " << ucClass->get_classCode() << "\n";

        vector<Lesson*> lessons = ucClass->get_lessons();

        for(Lesson *lesson: lessons){

            cout << lesson->get_weekday() << " " << lesson->get_type() << " " << lesson->get_starthour() << " " << lesson->get_duration() << "\n";
        }
    }
}