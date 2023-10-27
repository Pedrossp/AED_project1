#ifndef AED_PROJECT1_CLASS_H
#define AED_PROJECT1_CLASS_H

#include <string>

using namespace std;


class Class {
public:
    Class(string& ClassCode, string& UcCode, string& Weekday, float& StartHour, float& Duration, string& Type);
    const string get_classcode();
    const string get_uccode();
    const string get_weekday();
    float get_starthour();
    float get_duration();
    const string get_type();


private:
    string ClassCode_;
    string UcCode_;
    string Weekday_;
    float StartHour_;
    float Duration_;
    string Type_;


};


#endif //AED_PROJECT1_CLASS_H
