#ifndef AED_PROJECT1_MENU_H
#define AED_PROJECT1_MENU_H

#include "DataManip.h"

class Menu {

private:
    DataManip data_;

public:
    Menu(DataManip data);
    int OptionsMenu();
    void run();


    void TimetablesMenu();
    void StudentsMenu();

    void checkStudentSchedule();
    void checkClassSchedule();


    //print functions
    void printStudentSchedule(int student_code);// por implementar
    void printClassSchedule(string class_code); // por implementar
    void wait();

    void RequestMenu();
};


#endif //AED_PROJECT1_MENU_H
