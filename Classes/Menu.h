#ifndef AED_PROJECT1_MENU_H
#define AED_PROJECT1_MENU_H

#include <list>
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

    void exitProgram() const;

    void SwitchMenu(Student *student);

    void AddMenu();

    void CancelMenu();



    UC_Class* askUcClass(Student *student);

    void AddMenu(Student *student);

    void CancelMenu(Student *student);

    int Students_Num_Ucs(Student *student);

    void sortStudents_byname(list<Student *> students);
    void sortStudents_bynameInv(list<Student *> students);
    void sortStudents_bycode(list<Student *> students);
    void sortStudents_bycodeInv(list<Student *> students);
    void sortStudents_byNum_Uc(list<Student *> students);
    void sortStudents_byNum_UcInv(list<Student *> students);



};


#endif //AED_PROJECT1_MENU_H
