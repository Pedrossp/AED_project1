#include <iostream>
#include "Menu.h"
#include "Consulting.h"

using namespace std;

Menu::Menu(DataManip data) {
    data_=data;
}
int Menu::OptionsMenu() {
    int option;
    cout    << endl << "========= OPTIONS =========" << endl <<"\n"
            << "1 Consult Timetables" << endl
            << "2 Consult Students"<< endl
            << "3 Submit a request" << endl
            << "4 Print pending requests" << endl
            << "5 Process requests" << endl
            << "6 Exit" << endl << "\n"
            << "What would you like to do next? " ;
    cin >> option; cout << endl;
    if (cin.fail()) {
        throw invalid_argument(">> Invalid number");
    }
    while(option < 1 || option > 6){
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    return option;
}

void Menu::run() {
    data_.read_classes_per_uc("../schedule/classes_per_uc.csv");
    data_.read_classes("../schedule/classes.csv");
    data_.read_students_classes("../schedule/students_classes.csv");

    while(true){
        int option = OptionsMenu();
        switch (option) {
            case 1: {
                TimetablesMenu();
                break;
            }
            case 2: {
                StudentsMenu();
                break;
            }
            
        }
    }




}

void Menu::TimetablesMenu() {
    cout   << endl << "========= Timetable Menu =========-" << endl <<"\n"
            << "1 Check the schedule of a student" << endl
            << "2 Check the schedule of a class"<< endl <<"\n"
            << "What would you like to do next? " ;
            int option;
            cin >>option;

    switch (option) {
        case 1: {
            checkStudentSchedule();
            wait();
        }
        case 2: {
            checkClassSchedule();
            wait();
        }

    }

}

void Menu::StudentsMenu() {
    cout   << endl << "========= Students Menu =========-" << endl <<"\n";

}

void Menu::checkStudentSchedule() {
    int student_code;
    cout << "Please insert the student's UP number: ";
    cin >> student_code;
    printStudentSchedule(student_code);
}

void Menu::checkClassSchedule() {
    string class_code;
    cout << "Please insert the class code : ";
    cin>> class_code;
    printClassSchedule(class_code);
}

void Menu::printStudentSchedule(int student_code) { // METER BONITO
    Consulting* consult = new Consulting(data_);

    vector<pair<vector<Lesson *>, pair<string, string>>> lessons_uc=consult->consultStudentSchedule(student_code);

    for(pair<vector<Lesson *>, pair<string, string>> lessons: lessons_uc){

        pair<string, string> pair = lessons.second;
        for(Lesson *lesson: lessons.first){

            cout <<lesson->get_weekday()  << " " << lesson->get_type() << " " << lesson->get_starthour() << " " << lesson->get_endhour() << " " << pair.first << " " << pair.second <<"\n";
        }
    }
}

void Menu::printClassSchedule(string class_code) { // METER BONITO
    Consulting *consult = new Consulting(data_);
    vector<pair<vector<Lesson *>, pair<string, string>>> lessons_uc =consult->consultClassSchedule(class_code);


    for(pair<vector<Lesson *>, pair<string, string>> lessons: lessons_uc){

        pair<string, string> pair = lessons.second;
        for(Lesson *lesson: lessons.first){

            cout <<lesson->get_weekday()  << " " << lesson->get_type() << " " << lesson->get_starthour() << " " << lesson->get_endhour() << " " << pair.first << " " << pair.second <<"\n";
        }
    }
}

void Menu::wait() {
    string input;
    cout << "Press any key to leave"<<endl;
    cin >> input;
        OptionsMenu();
}



