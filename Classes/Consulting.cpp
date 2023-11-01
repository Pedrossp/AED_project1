//
// Created by edu on 31-10-2023.
//
#include <iostream>

#include "Consulting.h"
#include "DataManip.h"
#include "UC_Class.h"

using namespace std;


Consulting::Consulting(DataManip data) {
    data_=data;
}

vector<pair<vector<Lesson *>, pair<string,string>>> Consulting::consultStudentSchedule(int student_code) {

    Student *student = data_.found_student(student_code);

    vector<Lesson*> lessons_;
    vector<UC_Class*> ucClasses = student->get_uc_classes();
    vector<pair<vector<Lesson *>, pair<string,string>>> lessons_uc;

    for(UC_Class *uc_class: ucClasses){

        vector<Lesson*> lessons = uc_class->get_lessons();

        for(Lesson *lesson: lessons){

            lessons_.push_back(lesson);
        }
        lessons_uc.push_back({lessons ,{uc_class->get_ucCode(),uc_class->get_classCode()}});
        lessons_.clear();
    }
    return lessons_uc;
}

vector<pair<vector<Lesson *>, pair<string,string>>> Consulting::consultClassSchedule(string class_code) { //a funçao xx ja esta a fazer o papel desta

    vector<UC_Class *> uc_classes = data_.get_uc_classes();
    vector<pair<vector<Lesson *>, pair<string,string>>> lessons_uc;
    vector<Lesson *> lessons;


    for(UC_Class *ucClass: uc_classes){

        if(ucClass->get_classCode()==class_code){

            for(Lesson *lesson: ucClass->get_lessons()){
                lessons.push_back(lesson);
            }

            lessons_uc.push_back({lessons ,{ucClass->get_ucCode(),ucClass->get_classCode()}});
            lessons.clear();
        }
    }

    return lessons_uc;
}

list<Student *> Consulting::consultStudentClass(string class_code) {

    list<Student *> consult_students;
    vector<Student *> students = data_.get_students();

    for (Student *student: students){

        vector<UC_Class *> uc_classes = student->get_uc_classes();

        for (UC_Class *uc_class: uc_classes){

            if (uc_class->get_classCode() == class_code){

                consult_students.push_back(student);
                break;
            }
        }
    }

    return consult_students;
}

list<Student *> Consulting::consultStudentUc(string uc_code) {

    list<Student *> consult_students;
    vector<Student *> students = data_.get_students();

    for (Student *student: students){

        vector<UC_Class *> uc_classes = student->get_uc_classes();

        for (UC_Class *uc_class: uc_classes){

            if (uc_class->get_ucCode() == uc_code){

                consult_students.push_back(student);
                break;
            }
        }
    }

    return consult_students;
}

list<Student *> Consulting::consultStudentYear(char year) {

    list<Student *> consult_students;
    vector<Student *> students = data_.get_students();

    for (Student *student: students) {

        vector<UC_Class *> uc_classes = student->get_uc_classes();

        for (UC_Class *uc_class: uc_classes){

            if (uc_class->get_classCode()[0] == year){

                consult_students.push_back(student);
                break;
            }
        }
    }

    return consult_students;
}

int Consulting::consultStudentsEnrolled(int n) {

    vector<Student *> students = data_.get_students();
    int result = 0;

    for (Student *student: students){

        vector<UC_Class *> uc_classes = student->get_uc_classes();
        int count = 0;

        for (UC_Class *uc_class: uc_classes){

            count++;
        }

        if (count >= n){
            result++;
        }
    }

    return result;
}

int Consulting::consultClassOcupation(string class_code) {

    vector<Student *> students = data_.get_students();
    int result = 0; // por acabar.......
}
