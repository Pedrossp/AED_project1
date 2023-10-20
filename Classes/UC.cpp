#include "UC.h"

UC::UC(string UcCode, vector <ClassCode> ClassCode){
    UcCode_ = UcCode;
    ClassCode_ = ClassCode;
}

string UC::get_code() {
    return UcCode_;
}