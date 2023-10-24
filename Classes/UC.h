#ifndef AED_PROJECT1_UC_H
#define AED_PROJECT1_UC_H
#include <string>
#include <vector>
#include "Class.h"


using namespace std;


class UC {
private:
    string UcCode_;
    vector<Class> ClassCode_;

public:
    UC(string UcCode, vector<Class> ClassCode);
    string get_code();

};


#endif //AED_PROJECT1_UC_H
