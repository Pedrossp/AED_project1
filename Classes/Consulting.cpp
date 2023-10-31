//
// Created by edu on 31-10-2023.
//

#include "Consulting.h"
#include "DataManip.h"
#include "UC_Class.h"


Consulting::Consulting(DataManip data) {
    data_=data;
}

list<Lesson *> Consulting::consultStudentSchedule(int student_code) {

    Student *student = data_.found_student(student_code);

    list<Lesson*> lessons_;

    vector<UC_Class*> ucClasses = student->get_uc_classes();

    for(UC_Class *uc_class: ucClasses){

        vector<Lesson*> lessons = uc_class->get_lessons();

        for(Lesson *lesson: lessons){

            lessons_.push_back(lesson);
        }
    }
    return lessons_;
}

list<Lesson *> Consulting::consultClassSchedule(string Class_code) {
    vector<UC_Class*> uc_cla;       //acabarrrrrrr
}