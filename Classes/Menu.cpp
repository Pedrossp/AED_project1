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
            case 4:
                data_.ShowPendingRequests();
                break;
            case 5: {
                data_.process_pendent_requests();
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
            int option1;
            cin >> option1;

    switch (option1) {
        case 1: {
            checkStudentSchedule();
            wait();
            break;
        }
        case 2: {
            checkClassSchedule();
            wait();
            break;
        }

    }

}

void Menu::StudentsMenu() {
    cout   << endl << "========= Students Menu ==========" << endl <<"\n"
            << "1 Search students by year" << endl
            << "2 Search students by uc" << endl
            << "3 Search students by class"<< endl
            << "4 Consult students enrolled in x number of uc's" << endl
            << "5 Back" << endl << "\n"
            << "What would you like to do next? " ;

            int option1;
            cin >> option1;

            Consulting *consult = new Consulting(data_);

    switch (option1) {
        case 1: {
            cout << "Which year do you want to consult? ";
            char year;
            cin >> year;
            list<Student*> students = consult->consultStudentYear(year);
            SortMenu(students);
            break;
        }
        case 2: {
            cout << "Please insert the uc code: ";
            string uc_code;
            cin >> uc_code;
            list<Student*> students = consult->consultStudentUc(uc_code);
            SortMenu(students);
            break;
        }
        case 3: {
            cout << "Please insert the uc class: ";
            string class_code;
            cin >> class_code;
            list<Student*> students = consult->consultStudentClass(class_code);
            SortMenu(students);
            break;
        }
        case 4: {
            cout << "Insert the number of uc's: ";
            int n;
            cin >> n;
            cout << "The number of students enrolled in " << n << " uc's is: " << consult->consultStudentsEnrolled(n) << "\n";
        }

    }

}

void Menu::SortMenu(list<Student*> students) {
    cout   << endl << "========= Sort Menu ==========" << endl <<"\n"
            << "1 Sort students by name (A-Z)" << endl
            << "2 Sort students by name (Z-A)" << endl
            << "3 Sort students by code (lower to higher)"<< endl
            << "4 Sort students by code (higher to lower)" << endl
            << "5 Sort students by number of uc's (lower to higher)" << endl
            << "6 Sort students by number of uc's (higher to lower)" << endl
            << "7 Back" << endl << "\n"
            << "What would you like to do next? " ;

            int option1;
            cin >> option1;

    switch (option1) {
        case 1: {
            sortStudents_byname(students);
            printListStudents(students);
            wait();
            break;
        }
        case 2: {
            sortStudents_bynameInv(students);
            printListStudents(students);
            wait();
            break;
        }
        case 3: {
            printListStudents(students);
            wait();
            break;
        }
        case 4: {
            sortStudents_bycodeInv(students);
            printListStudents(students);
            wait();
            break;
        }
        case 5: {
            sortStudents_byNum_Uc(students);
            printListStudents(students);
            wait();
            break;
        }
        case 6: {
            sortStudents_byNum_UcInv(students);
            printListStudents(students);
            wait();
            break;
        }

    }
}

void Menu::RequestMenu() {
    cout   << endl << "========= Request Menu ==========" << endl <<"\n";
    cout << endl;
    cout << "Please insert the student's UP number:" <<endl;
    int student_code;
    cin>>student_code;

    Student* student =data_.found_student(student_code);

    if(student == nullptr){
        // pagina de erro
        cout << "n foi encontrado";
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


        switch (option) {
            case (1): {
                data_.switch_class(student,initialUcCode, finalClass);
                break;
            }
            case(2): {
                Request *req = new Request(*student,initialUcCode,finalClass,"switch");
                data_.set_pendent_requests(req);
                break;
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


        switch (option) {
            case (1): {
                data_.join_new_ucClass(student->get_code(),finalUcCode,finalClass);
                break;
            }
            case(2): {
                Request *req = new Request(*student,finalUcCode,finalClass,"join");
                data_.set_pendent_requests(req);
                break;
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

        switch (option) {
            case (1): {
                data_.leave_ucClass(student,removeUcCode);
                break;
            }
            case(2): {

                Request *req = new Request(*student,removeUcCode,empty,"leave");
                data_.set_pendent_requests(req);
                break;
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
    cout << "Please insert the class code: ";
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

            cout << lesson->get_weekday()  << " " << lesson->get_type() << " " << lesson->get_starthour() << " " << lesson->get_endhour() << " " << pair.first << " " << pair.second <<"\n";
        }
    }
}

void Menu::printListStudents(list<Student*> students) {
    for(Student *student : students) {
        cout << student->get_name() << " " << student->get_code() << "\n";
    }
}

void Menu::wait() {
    string input;
    cout << "Press any key to leave"<<endl;
    cin >> input;
}

void Menu::exitProgram() const {
    cout << endl << "Saving changes..." << endl;
    data_.fileWriter("../schedule/students_classes_updated.csv");
    cout << endl << "Exiting program..." << endl;
    exit(0);
}


int Menu::Students_Num_Ucs(Student *student){
    int count = 0;
    vector<UC_Class*> uc_classes = student->get_uc_classes();

    for (UC_Class *uc_class : uc_classes){
        count ++;
    }

    return count;
}

// Funções Sort

void Menu::sortStudents_byname(list<Student*>& students) {
    students.sort([](Student* student1, Student* student2) {
        return student1->get_name() < student2->get_name();
    });
}

void Menu::sortStudents_bynameInv(list<Student*>& students) {
    students.sort([](Student* student1, Student* student2) {
        return student1->get_name() > student2->get_name();
    });
}

void Menu::sortStudents_bycode(list<Student *>& students) {
    students.sort([](Student* student1, Student* student2) {
        return student1->get_code() < student2->get_code();
    });
}

void Menu::sortStudents_bycodeInv(list<Student *>& students) {
    students.sort([](Student* student1, Student* student2) {
        return student1->get_code() > student2->get_code();
    });
}

void Menu::sortStudents_byNum_Uc(list<Student *>& students) {
    students.sort([this](Student* student1, Student* student2) {
        int num1 = Students_Num_Ucs(student1);
        int num2 = Students_Num_Ucs(student2);
        return num1 < num2;
    });
}

void Menu::sortStudents_byNum_UcInv(list<Student *>& students) {
    students.sort([this](Student* student1, Student* student2) {
        int num1 = Students_Num_Ucs(student1);
        int num2 = Students_Num_Ucs(student2);
        return num1 > num2;
    });
}