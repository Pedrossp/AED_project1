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
            << "4 Show pending requests" << endl
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
            case 3: {
                RequestMenu();
                break;
            }
            case 6 : {
                exitProgram();
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
    cout   << endl << "========= Students Menu ==========" << endl <<"\n";

}

void Menu::RequestMenu() {
    cout   << endl << "========= Request Menu ==========" << endl <<"\n";
    cout << endl;
    cout << "Please insert the student's UP number:" <<endl;
    int student_code;
    cin>>student_code;

    Student* student =data_.found_student(student_code);

    if(student->get_code() == -1){
        // pagina de erro
    }
    else {
        cout << "This student is enrolled in the following classes: " << endl; // rever cout
        student->print_ucClass_student();
        cout << "Select the type of request you want to submit: " << endl; // rever cout
        cout << endl << "1 Switch student class " << endl
             << "2 Enroll in a new Uc"  << "\n"
             << "3 Cancel uc registration";
        int option;
        cin >> option;
        while (true) {
            switch (option) {
                case (1): {
                    SwitchMenu(student);
                    break;
                }
                case(2): {
                    AddMenu(student);
                    break;
                }
                case(3): {
                    CancelMenu(student);
                    break;
                }

            }

        }
    }
}

void Menu::SwitchMenu(Student *student) {

    cout << "Please insert the uc code: " ;
    string initialUcCode;
    cin >> initialUcCode;

    cout << "Please enter the class you want to switch to: ";
    string finalClass;
    cin>>finalClass;

    cout << "Select one option: " <<endl;// atenção ao cout á trolha
    cout << endl
        << "1 Instant request handling" << endl
        << "2 Add to pending requests" << endl << "\n"
        << " "; // voltar atras
    int option;
    cin >> option;

    while(true){
        switch (option) {
            case (1): {
                data_.switch_class(student,initialUcCode, finalClass);
                exitProgram();
            }
            case(2): {
                Request *req = new Request(*student,initialUcCode,finalClass,"switch");
                data_.set_pendent_requests(req);
            }
        }
    }
}

void Menu::AddMenu(Student *student) {
    cout << "Please insert the uc code: " ;
    string finalUcCode;
    cin >> finalUcCode;

    cout << "Please enter the class you want to join to: ";
    string finalClass;
    cin>>finalClass;
    cout << "Select one option: " <<endl;// atenção ao cout á trolha
    cout << endl
         << "1 Instant request handling" << endl
         << "2 Add to pending requests" << endl << "\n"
         << " "; // voltar atras
    int option;
    cin >> option;

    while(true){
        switch (option) {
            case (1): {
                data_.join_new_ucClass(student,finalUcCode,finalClass);
                exitProgram();
            }
            case(2): {
                Request *req = new Request(*student,finalUcCode,finalClass,"join");
                data_.set_pendent_requests(req);
            }
        }
    }
}

void Menu::CancelMenu(Student *student) {
    cout << "Please insert the uc code: " ;
    string removeUcCode;
    cin >> removeUcCode;

    cout << "Select one option: " <<endl;// atenção ao cout á trolha
    cout << endl
         << "1 Instant request handling" << endl
         << "2 Add to pending requests" << endl << "\n"
         << " "; // voltar atras
    int option;
    cin >> option;

    string empty= "";
    while(true){
        switch (option) {
            case (1): {
                data_.leave_ucClass(student,removeUcCode);
            }
            case(2): {

                Request *req = new Request(*student,removeUcCode,empty,"leave");
                data_.set_pendent_requests(req);
            }
        }
    }
}

/*UC_Class* Menu::askUcClass(Student* student) {
    cout << "Please insert the uc code: " ;
    string ucCode,classCode;
    cin >> ucCode;

    UC_Class* ucClass = new UC_Class(ucCode,data_.found_classCode_student(ucCode,student));
    return ucClass;

}
*/
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

void Menu::exitProgram() const {
    cout << endl << "Saving changes..." << endl;
    data_.fileWriter("../schedule/students_classes_updated.csv");
    cout << endl << "Exiting program..." << endl;
    exit(0);
}