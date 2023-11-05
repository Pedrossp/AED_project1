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
    cout << endl << endl
    << "Which file do you want to read: " << endl << endl
    << "|1 Default students file            |" << endl
    << "|2 Updated students file            |" << endl;
    char option;
    cin>> option;
    switch (option) {
        case ('1') : {
            data_.read_students_classes("../schedule/students_classes.csv");
            break;
        }
        case('2') : {
            data_.read_students_classes("../schedule/students_classes_updated.csv");
            break;
        }

    }
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
                flag =false;
                break;
            }
            case (2): {
                AddMenu(student);
                flag = false;
                break;
            }
            case (3): {
                CancelMenu(student);
                flag=false;
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



bool compareLessons(Lesson* lhs, Lesson* rhs) {
    // Comparar primeiro por dia da semana
    if (lhs->get_weekday() != rhs->get_weekday()) {
        return lhs->get_weekday() < rhs->get_weekday();
    }
    // Em caso de empate no dia da semana, comparar por hora de início
    return lhs->get_starthour() < rhs->get_starthour();
}

void Menu::printStudentSchedule(int student_code) {
    cout << "Student schedule nº " << student_code << endl<<endl;

    Consulting* consult = new Consulting(data_);
    vector<std::pair<vector<Lesson*>, pair<string, string>>> lessons_uc = consult->consultStudentSchedule(student_code);

    const vector<string> weekdays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    // Organizar as aulas por dia da semana
    map<string, vector<Lesson*>> lessonsByDay;

    for (const auto& lessons_pair : lessons_uc) {
        const auto& lessons = lessons_pair.first;

        for (Lesson* lesson : lessons) {
            lessonsByDay[lesson->get_weekday()].push_back(lesson);
        }
    }

    // Classificar as aulas por dia da semana e hora de início
    for (auto& day_lessons : lessonsByDay) {
        auto& lessons = day_lessons.second;
        sort(lessons.begin(), lessons.end(), compareLessons);
    }

    // Imprimir as aulas na ordem correta
    for (const auto& day : weekdays) {
        auto it = lessonsByDay.find(day);

        if (it != lessonsByDay.end()) {
            for (Lesson* lesson : it->second) {
                cout << day << " " << lesson->get_type() << " "
                          << lesson->get_starthour() << " " << lesson->get_endhour() << " "
                          << lessons_uc[0].second.first << " " << lessons_uc[0].second.second << "\n";
            }
        }
    }

    delete consult;
}


void Menu::printClassSchedule(string class_code) { // METER BONITO
    cout << "Class " << class_code << " schedule " << endl<< endl;
    Consulting* consult = new Consulting(data_);
    std::vector<std::pair<std::vector<Lesson*>, std::pair<std::string, std::string>>> lessons_uc = consult->consultClassSchedule(class_code);

    const std::vector<std::string> weekdays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    // Organizar as aulas por dia da semana
    std::map<std::string, std::vector<Lesson*>> lessonsByDay;

    for (const auto& lessons_pair : lessons_uc) {
        const auto& lessons = lessons_pair.first;

        for (Lesson* lesson : lessons) {
            lessonsByDay[lesson->get_weekday()].push_back(lesson);
        }
    }

    // Classificar as aulas por dia da semana e hora de início
    for (auto& day_lessons : lessonsByDay) {
        auto& lessons = day_lessons.second;
        std::sort(lessons.begin(), lessons.end(), compareLessons);
    }

    // Imprimir as aulas na ordem correta
    for (const auto& day : weekdays) {
        auto it = lessonsByDay.find(day);

        if (it != lessonsByDay.end()) {
            for (Lesson* lesson : it->second) {
                std::cout << day << " " << lesson->get_type() << " "
                          << lesson->get_starthour() << " " << lesson->get_endhour() << " "
                          << lessons_uc[0].second.first << " " << lessons_uc[0].second.second << "\n";
            }
        }
    }

    delete consult;
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