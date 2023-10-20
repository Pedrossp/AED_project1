#ifndef AED_PROJECT1_UC_H
#define AED_PROJECT1_UC_H
#include <string>

using namespace std;


class UC {
private:
    string UcCode_;
    vector <ClassCode> ClassCode_;

public:
    UC(string UcCode, vector <ClassCode> ClassCode);
    string get_code();

};


#endif //AED_PROJECT1_UC_H
