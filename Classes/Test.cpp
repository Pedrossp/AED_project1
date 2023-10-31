#include <iostream>
#include <list>

#include "Test.h"
#include "DataManip.h"
#include "Consulting.h"
#include "Lesson.h"

Test::Test(DataManip data){
    data_ = data;
}

void Test::test1() {

    vector<UC_Class *> uc = data_.get_uc_classes();

    for (UC_Class*a : uc) {

        cout<<a->get_ucCode() <<" " <<a->get_classCode()<<"\n";

    }
}

void Test::test_read_student_classes() {

    vector<Student *> students =data_.get_students();

    for(Student *student: students){

        cout << student->get_name() << ": "<< student->get_code() << "\n";

        vector<UC_Class *> uccs = student->get_uc_classes();

        for(UC_Class *ucc: uccs){

            cout << ucc->get_classCode() << ", " << ucc->get_ucCode() << "\n";
        }
    }
}

void Test::test_read_classes() {

    vector<UC_Class *> uc_classes =data_.get_uc_classes();

    for(UC_Class * ucClass: uc_classes){

        cout << ucClass->get_ucCode() << " " << ucClass->get_classCode() << "\n";

        vector<Lesson*> lessons = ucClass->get_lessons();

        for(Lesson *lesson: lessons){

            cout << lesson->get_weekday() << " " << lesson->get_type() << " " << lesson->get_starthour() << " " << lesson->get_endhour() << "\n";
        }
    }
}

void Test::test_consultStudentSchedule() {

    Consulting *consult = new Consulting(data_);

    int student_code = 202053367;

    list<Lesson *> lessons = consult->consultStudentSchedule(student_code);

    for(Lesson *lesson: lessons){

        cout <<lesson->get_weekday()  << " " << lesson->get_type() << " " << lesson->get_starthour() << " " << lesson->get_endhour() << "\n";
    }
}

void Test::test_xx() {

    vector<Lesson*> lessons = data_.xx("1LEIC01");

    for(Lesson *lesson: lessons){

        cout <<lesson->get_weekday()  << " " << lesson->get_type() << " " << lesson->get_starthour() << " " << lesson->get_endhour() <<"\n";
    }
}
