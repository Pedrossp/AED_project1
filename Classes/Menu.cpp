#include <iostream>
#include <limits>
#include <sstream>
#include "Menu.h"
#include "Consulting.h"



using namespace std;

Menu::Menu(DataManip data) {
    data_=data;
}
char Menu::OptionsMenu() {
    char option;
    cout    << endl << endl;
    cout    << endl << "|============ OPTIONS ==============|" << endl
                    << "|                                   |" << endl
                    << "|1 Consult Timetables               |" << endl
                    << "|2 Consult Students                 |" << endl
                    << "|3 Submit a request                 |" << endl
                    << "|4 Show pending requests            |" << endl
                    << "|5 Process requests                 |" << endl
                    << "|6 Exit                             |" << endl
                    << endl
                    << "What would you like to do next? "; cin >> option; cout << endl;

    if (cin.fail()) {
        throw invalid_argument(">> Invalid number");
    }
    while(static_cast<int>(option) < 49 || static_cast<int>(option) > 54){
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    return option;
}

void Menu::run() {
    data_.read_classes_per_uc("../schedule/classes_per_uc.csv");
    data_.read_classes("../schedule/classes.csv");
    data_.read_students_classes("../schedule/students_classes.csv");

    while(true){
        char option = OptionsMenu();
        switch (option) {
            case '1': {
                TimetablesMenu();
                break;
            }
            case '2': {
                StudentsMenu();
                break;
            }
            case '3': {
                RequestMenu();
                break;
            }
            case '4':
                data_.ShowPendingRequests();
                break;
            case '5': {
                data_.process_pendent_requests();
                break;
            }
            case '6': {
                exitProgram();
            }
        }
    }
}

void Menu::TimetablesMenu() {
    bool flag = true;
    while(flag) {
    cout    << endl
            << endl
            << endl << "========= Timetable Menu =========-" << endl
            << endl
            << "1 Check the schedule of a student" << endl
            << "2 Check the schedule of a class"<< endl
            << "0 Back" << endl
            << endl
            << "What would you like to do next? " ;
            char option1;
            cin >> option1; cout << endl;

    while(static_cast<int>(option1) < 48 || static_cast<int>(option1) > 50){
        cout << ">> Please choose a valid option: "; cin >> option1; cout << endl;
    }

        switch (option1) {
            case '1': {
                checkStudentSchedule();
                wait();
                break;
            }
            case '2': {
                checkClassSchedule();
                wait();
                break;
            }
            case '0': {
                flag = false;
                break;
            }
        }
    }
}

void Menu::StudentsMenu() {
    cout   << endl << "========= Students Menu ==========" << endl <<"\n"
            << "1 Search students by year" << endl
            << "2 Search students by uc" << endl
            << "3 Search students by class"<< endl
            << "4 Consult students enrolled in x number of uc's" << endl
            << "0 Back" << endl << "\n"
            << "What would you like to do next? " ;

    char option1;
    cin >> option1;

    Consulting *consult = new Consulting(data_);

    bool flag = true;
    while(flag) {

        switch (option1) {
            case ('0'):{
                flag = false;
                break;
            }
            case ('1'): {
                cout << "-> Back(0)" << endl
                     << "Which year do you want to consult? " ;

                char year;
                cin >> year;

                if (year == '0'){
                    flag = false;
                    break;
                }

                else if ( static_cast<int>(year) < 49 || static_cast<int>(year) > 51){
                    cout << "The year is not valid" << endl
                         << endl;
                    break;
                }

                cout << endl;
                list<Student *> students = consult->consultStudentYear(year);
                SortMenu(students);
                break;

            }
            case ('2'): {
                cout << "-> Back(0)" << endl
                     << "Which UC do you want to consult? " ;

                string uc_code;
                cin >> uc_code;

                if (uc_code == "0"){
                    flag = false;
                    break;
                }
                else if (!data_.found_if_uc_code(uc_code)){
                    cout << "This Uc does not exist" << endl
                         << endl;
                    break;
                }

                cout << endl;
                list<Student *> students = consult->consultStudentUc(uc_code);
                SortMenu(students);
                break;
            }
            case ('3'): {
                cout << "-> Back(0)" << endl
                     << "Which class do you want to consult? " ;

                string class_code;
                cin >> class_code;

                if (class_code == "0"){
                    flag = false;
                    break;
                }
                else if (!data_.found_if_class_code(class_code)){
                    cout << "This Uc does not exist" << endl
                         << endl;
                    break;
                }

                cout << endl;
                list<Student *> students = consult->consultStudentClass(class_code);
                SortMenu(students);
                break;
            }
            case ('4'): {
                int n;

                do {
                    cout << "Insert the number of UC's (0-7): ";

                    // Verifica se a entrada é um número válido
                    if (!(cin >> n)) {
                        cout << "Invalid input. Please enter a valid number." << endl << endl;
                        cin.clear();  // Limpa o estado de erro
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignora a entrada inválida
                        continue;  // Reinicia o loop para solicitar uma nova entrada
                    }

                    if (n >= 0 && n <= 7) {
                        cout << "The number of students enrolled in " << n << " UC's is: "
                             << consult->consultStudentsEnrolled(n) << endl << endl;
                        wait();
                        flag = false;
                    } else {
                        cout << "Invalid input. Please choose a valid option (0-7)." << endl;
                    }

                } while (flag);
                break;
            }

            default:
                cout << ">> Please choose a valid option: ";
                cin >> option1;
                cout << endl;

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
            << "0 Back" << endl << "\n"
            << "What would you like to do next? " ;

    char option1;
    cin >> option1;
    cout << endl;

    while(static_cast<int>(option1) < 48 || static_cast<int>(option1) > 54){
        cout << ">> Please choose a valid option: "; cin >> option1; cout << endl;
    }

    switch (option1) {
        case '0': {
            break;
        }
        case '1': {
            sortStudents_byname(students);
            printListStudents(students);
            wait();
            break;
        }
        case '2': {
            sortStudents_bynameInv(students);
            printListStudents(students);
            wait();
            break;
        }
        case '3': {
            printListStudents(students);
            wait();
            break;
        }
        case '4': {
            sortStudents_bycodeInv(students);
            printListStudents(students);
            wait();
            break;
        }
        case '5': {
            sortStudents_byNum_Uc(students);
            printListStudents(students);
            wait();
            break;
        }
        case '6': {
            sortStudents_byNum_UcInv(students);
            printListStudents(students);
            wait();
            break;
        }
    }
}

void Menu::RequestMenu() {
    cout << "Please insert the student's UP number: ";
    int student_code;
    cin>>student_code; cout << endl
       << endl
       << endl
       << endl;

    Student* student =data_.found_student(student_code);

    if(student == nullptr){
        // pagina de erro
        cout << "n foi encontrado";
    }
    else {

        bool flag = true;
    while(flag) {
        cout << endl << "================== Request Menu ===================" << endl
             << endl;
        cout << "This student is enrolled in the following classes: " << endl;
        student->print_ucClass_student();
        cout << endl
             << "1 Switch student class " << endl
             << "2 Enroll in a new Uc" << endl
             << "3 Cancel uc registration" << endl
             << endl
             << "Select the type of request you want to submit: ";
        int option;
        cin >> option;
        cout << endl;


        switch (option) {
            case (1): {
                SwitchMenu(student);
                break;
            }
            case (2): {
                AddMenu(student);
                break;
            }
            case (3): {
                CancelMenu(student);
                break;
            }
            case (4): {
                flag = false;
                break;
            }

        }

    }
    }
}

void Menu::SwitchMenu(Student *student) {

    cout << "-> Back (0)" << endl;
    cout << "Please insert the uc code: ";
    string initialUcCode;
    cin >> initialUcCode;

    if (initialUcCode == "0") {
        cout << endl
             << endl
             << endl;
        return;
    }

    cout << "Please enter the class you want to switch to: ";
    string finalClass;
    cin >> finalClass;

    bool flag = true;
    while (flag) {
        cout << "Select one option: " << endl;// atenção ao cout á trolha
        cout << endl
             << "1 Instant request handling" << endl
             << "2 Add to pending requests" << endl
             << "0 Back " << endl << endl;

        char option;
        cin >> option;


        switch (option) {
            case ('1'): {
                data_.switch_class(student, initialUcCode, finalClass);
                wait();
                flag = false;
                break;
            }
            case ('2'): {
                Request *req = new Request(*student, initialUcCode, finalClass, "switch");
                data_.set_pendent_requests(req);
                flag = false;
                break;
            }
            case ('0'): {
                flag = false;
                break;
            }
            default: {
                cout << "Please insert a valid option";
                break;

            }
        }
    }
}

void Menu::AddMenu(Student *student) {

    cout << "-> Back (0)" << endl;
    cout << "Please insert the uc code: " ;
    string finalUcCode;
    cin >> finalUcCode;

    if (finalUcCode == "0" ){
        cout << endl
             << endl
             << endl;
        return;
    }

    cout << "Please enter the class you want to join to: ";
    string finalClass;
    cin>>finalClass;

    bool flag = true;
    while(flag) {
    cout << endl << "Select one option: " <<endl;// atenção ao cout á trolha
    cout << endl
         << "1 Instant request handling" << endl
         << "2 Add to pending requests" << endl
         << "0 Back" << endl << endl;


        char option;
        cin >> option;

        switch (option) {
            case ('1'): {
                data_.join_new_ucClass(student->get_code(), finalUcCode, finalClass);
                wait();
                flag = false;
                break;
            }
            case ('2'): {
                Request *req = new Request(*student, finalUcCode, finalClass, "join");
                data_.set_pendent_requests(req);
                flag = false;
                break;
            }
            case ('0'): {
                flag = false;
                break;
            }
            default: {
                cout << "Please insert a valid option";
                break;

            }
        }
    }
}

void Menu::CancelMenu(Student *student) {
    cout << "-> Back (0)" << endl;
    cout << "Please insert the uc code: " ;
    string removeUcCode;
    cin >> removeUcCode;

    if (removeUcCode == "0") {
        cout << endl
             << endl
             << endl;
        return;
    }

    bool flag = true;
    while (flag) {
        cout << "Select one option: " << endl;// atenção ao cout á trolha
        cout << endl
             << "1 Instant request handling" << endl
             << "2 Add to pending requests" << endl
             << "0 Back " << endl << endl;

        char option;
        cin >> option;

        string empty = "";

        switch (option) {
            case ('1'): {
                data_.leave_ucClass(student, removeUcCode);
                wait();
                flag = false;
                break;
            }
            case ('2'): {

                Request *req = new Request(*student, removeUcCode, empty, "leave");
                data_.set_pendent_requests(req);
                flag = false;
                break;
            }
            case ('0'): {
                flag = false;
                break;
            }
            default: {
                cout << "Please insert a valid option";
                break;

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
    while (true) {

        cout << "Please insert the student's UP number: ";
        cin >> student_code;

        if (!cin.fail()) {
            break;
        }

        cout << "Invalid input. Please enter a valid UP number." << endl
             << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout << endl;
    // Loop para garantir que o aluno exista
    while (data_.found_student(student_code) == nullptr) {
        cout << "This student does not exist. Please enter a valid UP number: ";
        cin >> student_code;
        cout << endl;
    }

    cout << endl;
    printStudentSchedule(student_code);
}

void Menu::checkClassSchedule() {
    string class_code;
    while (true) {
        cout << "Please insert the class code: ";
        cin >> class_code;

        if (!cin.fail()) {
            break;
        }

        cout << "Invalid input. Please enter a valid class code." << endl
             << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout << endl;
    // Loop para garantir que o aluno exista
    while (!data_.found_if_class_code(class_code)) {
        cout << "This class does not exist. Please enter a valid class code: ";
        cin >> class_code;
        cout << endl;
    }

    cout << endl;
    printClassSchedule(class_code);
}

void Menu::printStudentSchedule(int student_code) { // METER BONITO

    cout << "Student schedule nº " << student_code << endl; // decidir o q fica aqui (numero, nome ou os dois)

    Consulting* consult = new Consulting(data_);
    vector<pair<vector<Lesson *>, pair<string, string>>> lessons_uc=consult->consultStudentSchedule(student_code);

    for(pair<vector<Lesson *>, pair<string, string>> lessons: lessons_uc){

        pair<string, string> pair = lessons.second;
        for(Lesson *lesson: lessons.first){

            cout <<lesson->get_weekday()  << " " << lesson->get_type() << " " << lesson->get_starthour() << " " << lesson->get_endhour() << " " << pair.first << " " << pair.second <<"\n";
        }
    }
    delete consult;   //verificar se n da errado
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
        cout << student->get_name() << ": " << student->get_code() << "\n";
    }
}

void Menu::wait() {
    string input;
    cout << endl << "Press any key to leave"<<endl;
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