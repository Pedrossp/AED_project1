#ifndef AED_PROJECT1_UC_H
#define AED_PROJECT1_UC_H
#include <string>
#include <vector>
#include "Lesson.h"


using namespace std;


class UC {

private:
    int UcCode_;
    vector<Lesson> ClassCode_;

public:
    UC(int UcCode, vector<Lesson> ClassCode);
    int get_code();

};


#endif //AED_PROJECT1_UC_H
