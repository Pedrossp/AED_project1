#ifndef AED_PROJECT1_LESSON_H
#define AED_PROJECT1_LESSON_H

#include <string>

using namespace std;


class Lesson {

private:
    int ClassCode_;
    int UcCode_;
    string Weekday_;
    float StartHour_;
    float Duration_;
    string Type_;

public:
    Lesson(int& ClassCode, int& UcCode, string& Weekday, float& StartHour, float& Duration, string& Type);
    const int get_classcode();
    const int get_uccode();
    const string get_weekday();
    float get_starthour();
    float get_duration();
    const string get_type();

};


#endif //AED_PROJECT1_LESSON_H
