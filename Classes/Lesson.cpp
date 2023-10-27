#include "Lesson.h"

using namespace std;


Lesson::Lesson() {
    Weekday_ = "";
    StartHour_ = 0;
    Duration_ = 0;
    Type_ = "";
}
Lesson::Lesson(string& Weekday, float& StartHour, float& Duration, string& Type) {
    Weekday_ = Weekday;
    StartHour_ = StartHour;
    Duration_ = Duration;
    Type_ = Type;
}

string const Lesson::get_weekday() {
    return Weekday_;
}

float const Lesson::get_starthour() {
    return StartHour_;
}

float const Lesson::get_duration() {
    return Duration_;
}

string const Lesson::get_type() {
    return Type_;
}