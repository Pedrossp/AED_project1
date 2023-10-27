#include "Lesson.h"

using namespace std;

Lesson::Lesson(string& ClassCode, string& UcCode, string& Weekday, float& StartHour, float& Duration, string& Type) {
    ClassCode_ = ClassCode;
    UcCode_ = UcCode;
    Weekday_ = Weekday;
    StartHour_ = StartHour;
    Duration_ = Duration;
    Type_ = Type;
}

const string Lesson::get_classcode() {
    return ClassCode_;
}

const string Lesson::get_uccode() {
    return UcCode_;
}

const string Lesson::get_weekday() {
    return Weekday_;
}

float Lesson::get_starthour() {
    return StartHour_;
}

float Lesson::get_duration() {
    return Duration_;
}

const string Lesson::get_type() {
    return Type_;
}