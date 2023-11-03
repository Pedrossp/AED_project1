#include <iostream>
#include <list>

#include "Test.h"
#include "DataManip.h"
#include "Consulting.h"
#include "Lesson.h"
#include "Menu.h"

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

    int student_code = 202031607;

    vector<pair<vector<Lesson *>, pair<string, string>>> lessons_uc = consult->consultStudentSchedule(student_code);

    for(pair<vector<Lesson *>, pair<string, string>> lessons: lessons_uc){

        pair<string, string> pair = lessons.second;
        for(Lesson *lesson: lessons.first){

            cout <<lesson->get_weekday()  << " " << lesson->get_type() << " " << lesson->get_starthour() << " " << lesson->get_endhour() << " " << pair.first << " " << pair.second <<"\n";
        }
    }

}

void Test::test_consultClassSchedule() {
    Consulting *consult = new Consulting(data_);
    vector<pair<vector<Lesson *>, pair<string, string>>> lessons_uc =consult->consultClassSchedule("1LEIC01");


    for(pair<vector<Lesson *>, pair<string, string>> lessons: lessons_uc){

        pair<string, string> pair = lessons.second;
        for(Lesson *lesson: lessons.first){

            cout <<lesson->get_weekday()  << " " << lesson->get_type() << " " << lesson->get_starthour() << " " << lesson->get_endhour() << " " << pair.first << " " << pair.second <<"\n";
        }
    }
}

void Test::test_consultStudentClass() {

    Consulting *consult = new Consulting(data_);
    list<Student *> students = consult->consultStudentClass("1LEIC05");

    for (Student *student: students){

        cout << student->get_name() << ": "<< student->get_code() << "\n";
    }
}

void Test::test_consultStudentUc() {

    Consulting *consult = new Consulting(data_);
    list<Student *> students = consult->consultStudentClass("1LEIC05");

    for (Student *student: students){

        cout << student->get_name() << ": "<< student->get_code() << "\n";
    }
}

void Test::test_consultStudentYear() {

    Consulting *consult = new Consulting(data_);
    list<Student *> students = consult->consultStudentYear('1');

    for (Student *student: students){

        cout << student->get_name() << ": "<< student->get_code() << "\n";
    }
}

void Test::test_consultStudentsEnrolled() {

    Consulting *consult = new Consulting(data_);
    int result = consult->consultStudentsEnrolled(1);

    cout << result;
}

void Test::test_consultClassOcupation() {

    Consulting *consult = new Consulting(data_);
    map<string, int> uc_number = consult->consultClassOcupation("1LEIC05");

    for (const auto& par : uc_number){

        cout << par.first << ": "<< par.second << "\n";
    }
}

void Test::test_consultMaxUc() {
    Consulting *consult = new Consulting(data_);
    string result = consult->consultMaxUc();

    cout << result;
}

void Test::test_leave_ucClass() {
    UC_Class *ucClass = new UC_Class("L.EIC005","1LEIC08");
    string a = "";
    Student *student = new Student(a,202031607);
    data_.leave_ucClass(student,ucClass);
    Menu menu(data_);
    menu.exitProgram();

}

void Test::test_classCode_student() {
    int code = 202071557;
    string uc_code = "L.EIC021";
    string class_code = data_.found_classCode_student(uc_code, data_.found_student(code));

    cout << class_code;

}



