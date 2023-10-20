#include "UC.h"

UC::UC(string UcCode){
    UcCode_ = UcCode;
}

string UC::get_code() {
    return UcCode_;
}