//
// Created by edu on 31-10-2023.
//

#include "Consulting.h"
#include "DataManip.h"
#include "UC_Class.h"


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
