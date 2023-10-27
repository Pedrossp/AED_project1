#include "Class.h"

using namespace std;

Class::Class(string& ClassCode, string& UcCode, string& Weekday, float& StartHour, float& Duration, string& Type) {
    ClassCode_ = ClassCode;
    UcCode_ = UcCode;
    Weekday_ = Weekday;
    StartHour_ = StartHour;
    Duration_ = Duration;
    Type_ = Type;
}

const string Class::get_classcode() {
    return ClassCode_;
}

const string Class::get_uccode() {
    return UcCode_;
}

const string Class::get_weekday() {
    return Weekday_;
}

float Class::get_starthour() {
    return StartHour_;
}

float Class::get_duration() {
    return Duration_;
}

const string Class::get_type() {
    return Type_;
}