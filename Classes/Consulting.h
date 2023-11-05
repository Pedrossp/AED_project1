//
// Created by edu on 31-10-2023.
//

#ifndef AED_PROJECT1_CONSULTING_H
#define AED_PROJECT1_CONSULTING_H

#include <list>
#include <map>
#include "Student.h"
#include "DataManip.h"

class Consulting {

private:
    DataManip data_;

public:
    Consulting(DataManip data);

    vector<pair<vector<Lesson *>, pair<string,string>>> consultStudentSchedule(int student_code);
    vector<pair<vector<Lesson *>, pair<string, string>>> consultClassSchedule(string class_code);

    list<Student*> consultStudentYear(char year);
    list<Student*> consultStudentUc(string uc_code);
    list<Student*> consultStudentClass(string class_code);

    int consultStudentsEnrolled(int n);

    string consultMaxUc();

    map<string, int> consultClassOcupation(string class_code);
};


#endif //AED_PROJECT1_CONSULTING_H
