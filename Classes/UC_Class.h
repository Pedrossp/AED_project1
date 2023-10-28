#ifndef AED_PROJECT1_UC_CLASS_H
#define AED_PROJECT1_UC_CLASS_H

#include "Lesson.h"

#include <string>
#include <vector>

using namespace std;


class UC_Class {

private:
    string UcCode_;
    string ClassCode_;
    vector<Lesson*> Lessons_;

public:
    UC_Class();
    UC_Class(string UcCode,string ClassCode);

    string const get_ucCode();
    string const get_classCode();
    vector<Lesson*> const get_lessons();

    void set_lessons(Lesson* Lessons);



};


#endif //AED_PROJECT1_UC_CLASS_H
