//
// Created by edu on 31-10-2023.
//

#ifndef AED_PROJECT1_CONSULTING_H
#define AED_PROJECT1_CONSULTING_H


#include <list>
#include "Student.h"
#include "DataManip.h"

class Consulting {

private:
    DataManip data_;

public:
    Consulting(DataManip data);

    list<Lesson*> consultStudentSchedule(int student_code);     //sera melhor usar map ou retornar logo o print???
    list<Lesson*> consultClassSchedule(string Class_code);
    list<Student*> consultYear(char number );

};


#endif //AED_PROJECT1_CONSULTING_H
