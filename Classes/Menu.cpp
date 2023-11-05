#include <iostream>
#include <limits>
#include <sstream>
#include "Menu.h"
#include "Consulting.h"



using namespace std;

Menu::Menu(DataManip data) {
    data_=data;
}
/**
 * @brief Apresenta o menu inicial do programa, exibe opções disponíveis e recebe a escolha do utilizador.
 *
 * @return A opção escolhida como um caractere.
 *
 * @throws std::invalid_argument se a entrada não for um número válido.
 *
 * @note A função utiliza cin.fail() para verificar entradas inválidas e garante que a entrada esteja dentro da faixa válida.
 *
 * @note Complexidade Temporal: O(1) - A complexidade temporal é constante porque o número de opções disponíveis é fixo, e a função realiza um número fixo de operações independentemente do tamanho da entrada.
 */
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
                    << "What would you like to do next? ";

    // Obtém a escolha do utilizador
    cin >> option;
    cout << endl;

    // Verifica se a entrada não é um número válido
    if (cin.fail()) {
        throw invalid_argument(">> Invalid number");
    }

    // Garante que a entrada esteja dentro da faixa válida
    while(static_cast<int>(option) < 49 || static_cast<int>(option) > 54){
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    return option;
}

/**
 * @brief Executa a funcionalidade principal do programa, incluindo a leitura de arquivos, exibição de menus e manipulação de escolhas do usuário.
 *
 * @note Esta função inicializa dados a partir de arquivos, permite ao usuário escolher um arquivo e entra em um loop para exibir e processar menus.
 *       O usuário pode escolher opções relacionadas a horários, estudantes, pedidos, entre outros.
 *
 * @note A complexidade temporal desta função depende da complexidade das operações nas funções subjacentes (por exemplo, leitura de arquivos, processamento de menus).
 *       Envolve a leitura de arquivos, entrada do usuário e processamento de menus, onde a complexidade temporal é influenciada pelo tamanho dos dados e pelo número de opções de menu.
 *
 * @note O loop nesta função executa indefinidamente até que o usuário escolha sair do programa.
 */
void Menu::run() {
    // Lê informações necessárias de classes de arquivos
    data_.read_classes_per_uc("../schedule/classes_per_uc.csv");
    data_.read_classes("../schedule/classes.csv");

    // Pergunta ao usuário qual arquivo de estudantes deseja ler
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
    // Loop principal para processar opções do usuário
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

/**
 * @brief Menu de Horários que permite ao utilizador escolher entre opções relacionadas a consultar horários de estudantes e classes.
 *
 * @note Este menu apresenta opções para verificar o horário de um estudante, verificar o horário de uma turma e voltar ao menu anterior.
 *
 * @note O utilizador pode escolher entre opções digitando um número correspondente à ação desejada.
 *
 * @note A complexidade temporal desta função depende principalmente do tempo de execução das operações dentro dos casos do switch.
 *       Os loops de verificação de opção e a execução das funções checkStudentSchedule e checkClassSchedule têm complexidade constante em relação ao tamanho dos dados.
 *
 * @note A função é executada enquanto o utilizador escolher opções diferentes de '0' para voltar ao menu anterior.
 */
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

        // Verificar se a opção é válida
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

/**
 * @brief Menu de Estudantes que permite ao utilizador escolher entre várias opções relacionadas à consulta de estudantes.
 *
 * @note Este menu oferece opções para pesquisar estudantes por ano, por unidade curricular (UC), por turma e para consultar estudantes inscritos em um número específico de UCs.
 *
 * @note O utilizador pode escolher entre opções digitando um número correspondente à ação desejada.
 *
 * @note A complexidade temporal desta função depende principalmente do tempo de execução das operações dentro dos casos do switch.
 *       As operações dentro dos casos incluem consultas a estudantes com base no ano, UC, classe e número de UCs inscritas.
 *
 * @note A função envolve interações com o utilizador, como entrada de ano, UC, classe e número de UCs, mas a complexidade de entrada não é dominante.
 *       A complexidade é principalmente influenciada pelo número de estudantes e operações realizadas dentro dos casos do switch.
 *
 * @note A função é executada enquanto o utilizador escolher opções diferentes de '0' para voltar ao menu anterior.
 */
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
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
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

/**
 * @brief Menu de Ordenação que permite ao utilizador escolher entre várias opções de ordenação para uma lista de estudantes.
 *
 * @param students Lista de ponteiros para objetos do tipo Student a serem ordenados.
 *
 * @note Este menu oferece opções para ordenar estudantes por nome (A-Z), nome (Z-A), código (menor para maior), código (maior para menor),
 *       número de UCs (menor para maior) e número de UCs (maior para menor).
 *
 * @note O utilizador pode escolher entre opções digitando um número correspondente à ação desejada.
 *
 * @note A complexidade temporal desta função depende principalmente do tempo de execução das operações dentro dos casos do switch.
 *       Cada caso chama uma função de ordenação específica, e a complexidade da ordenação é o fator determinante.
 *
 * @note A função envolve interações com o utilizador para obter a opção de ordenação e a execução da operação de ordenação na lista de estudantes.
 *
 * @note A função retorna a lista de estudantes ordenada ou não modificada, dependendo da opção escolhida.
 */
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

    // Verificar se a opção é válida
    while(static_cast<int>(option1) < 48 || static_cast<int>(option1) > 54){
        cout << ">> Please choose a valid option: "; cin >> option1; cout << endl;
    }

    // Executar a operação correspondente à opção escolhida
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

/**
 * @brief Menu de Pedidos que permite ao utilizador escolher entre várias opções relacionadas a solicitações de um estudante.
 *
 * @note Este menu oferece opções para trocar a turma de um estudante, inscrever-se em uma nova UC e cancelar a inscrição em uma UC.
 *
 * @note O utilizador deve inserir o número de UP do estudante para o qual deseja fazer as solicitações.
 *
 * @note A complexidade temporal desta função depende principalmente do tempo de execução das operações dentro dos casos do switch.
 *       Cada caso chama uma função específica para processar a solicitação escolhida.
 *
 * @note A função envolve interações com o utilizador para obter o número de UP do estudante e a escolha da operação desejada.
 *
 * @note A função cria um loop até que o utilizador escolha sair do menu de pedidos.
 *
 * @param student_code Número de UP do estudante para o qual deseja fazer as solicitações.
 */
void Menu::RequestMenu() {
    cout << "Please insert the student's UP number: ";
    int student_code;
    cin>>student_code; cout << endl
       << endl
       << endl
       << endl;

    // Encontrar o estudante com base no número de UP fornecido
    Student* student =data_.found_student(student_code);

    if(student == nullptr){
        // pagina de erro
        cout << "This student was not found";
    }
    else {
        // Loop principal para o menu de pedidos
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

            // Executar a operação correspondente à opção escolhida
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

/**
 * @brief Menu de Troca de Turma que permite ao utilizador solicitar uma mudança de turma para uma UC específica.
 *
 * @param student Ponteiro para o objeto Student para o qual a troca de turma será solicitada.
 *
 * @note O utilizador deve inserir o código da UC inicial e a turma final desejada.
 *
 * @note A função cria um loop até que o utilizador escolha sair do menu de troca de turma.
 *
 * @param student Ponteiro para o objeto Student para o qual a troca de turma será solicitada.
 */
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

    // Loop principal para o menu de troca de turma
    bool flag = true;
    while (flag) {
        cout << "Select one option: " << endl;
        cout << endl
             << "1 Instant request handling" << endl
             << "2 Add to pending requests" << endl
             << "0 Back " << endl << endl;

        char option;
        cin >> option;

        // Executar a operação correspondente à opção escolhida
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

/**
 * @brief Menu de Adição de UC que permite ao utilizador solicitar a adição a uma nova UC e turma.
 *
 * @param student Ponteiro para o objeto Student para o qual a adição de UC será solicitada.
 *
 * @note O utilizador deve inserir o código da UC final e a turma desejada.
 *
 * @note A função cria um loop até que o utilizador escolha sair do menu de adição de UC.
 *
 * @param student Ponteiro para o objeto Student para o qual a adição de UC será solicitada.
 *
 * @note A complexidade temporal desta função é principalmente determinada pelo tempo de execução das operações dentro do loop, como a criação de objetos Request, a adição de pedidos pendentes e a execução imediata do pedido de adição de UC.
 */
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

    // Loop principal para o menu de adição de UC
    bool flag = true;
    while(flag) {
    cout << endl << "Select one option: " <<endl;
    cout << endl
         << "1 Instant request handling" << endl
         << "2 Add to pending requests" << endl
         << "0 Back" << endl << endl;


        char option;
        cin >> option;

        // Executar a operação correspondente à opção escolhida
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

/**
 * @brief Menu de Cancelamento de UC que permite ao utilizador solicitar a remoção de uma UC.
 *
 * @param student Ponteiro para o objeto Student para o qual a remoção de UC será solicitada.
 *
 * @note O utilizador deve inserir o código da UC que deseja remover.
 *
 * @note A função cria um loop até que o utilizador escolha sair do menu de cancelamento de UC.
 *
 * @param student Ponteiro para o objeto Student para o qual a remoção de UC será solicitada.
 *
 * @note A complexidade temporal desta função é principalmente determinada pelo tempo de execução das operações dentro do loop, como a criação de objetos Request, a adição de pedidos pendentes e a execução imediata do pedido de remoção de UC.
 */
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

    // Loop principal para o menu de cancelamento de UC
    bool flag = true;
    while (flag) {
        cout << "Select one option: " << endl;
        cout << endl
             << "1 Instant request handling" << endl
             << "2 Add to pending requests" << endl
             << "0 Back " << endl << endl;

        char option;
        cin >> option;

        string empty = "";

        // Executar a operação correspondente à opção escolhida
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

/**
 * @brief Função para verificar o horário de um estudante.
 *
 * @note O utilizador é solicitado a inserir o número de aluno (UP number).
 *
 * @note A função inclui verificações para garantir que a entrada é um número inteiro válido e que o aluno existe.
 *
 * @note A complexidade temporal é dominada pelo número de tentativas necessárias para obter uma entrada válida e verificar a existência do aluno na base de dados.
 */
void Menu::checkStudentSchedule() {

    int student_code;

    // Loop para garantir que o número inserido é um número inteiro válido
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

    // Uma vez que o número do aluno é válido e o aluno existe, imprimir o horário do aluno
    printStudentSchedule(student_code);
}

/**
 * @brief Função para verificar o horário de uma classe.
 *
 * @note O utilizador é solicitado a inserir o código da classe.
 *
 * @note A função inclui verificações para garantir que a entrada é uma string válida e que a classe existe.
 *
 * @note A complexidade temporal é dominada pelo número de tentativas necessárias para obter uma entrada válida e verificar a existência da classe na base de dados.
 */
void Menu::checkClassSchedule() {

    string class_code;

    // Loop para garantir que o código inserido é uma string válida
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

    // Uma vez que o código da classe é válido e a classe existe, imprimir o horário da classe
    printClassSchedule(class_code);
}


/**
 * @brief Função de comparação para ordenar aulas com base no dia da semana e hora de início.
 *
 * @param lhs Ponteiro para a primeira aula a ser comparada.
 * @param rhs Ponteiro para a segunda aula a ser comparada.
 *
 * @return Retorna verdadeiro se a primeira aula deve estar antes da segunda, falso caso contrário.
 *
 * @note Esta função é utilizada como critério de ordenação ao organizar as aulas.
 *
 * @note A complexidade temporal é constante, pois envolve apenas operações de comparação simples e aritmética básica.
 */
bool compareLessons(Lesson* lhs, Lesson* rhs) {
    // Comparar primeiro por dia da semana
    if (lhs->get_weekday() != rhs->get_weekday()) {
        return lhs->get_weekday() < rhs->get_weekday();
    }
    // Em caso de empate no dia da semana, comparar por hora de início
    return lhs->get_starthour() < rhs->get_starthour();
}

/**
 * @brief Imprime o horário de um estudante, organizado por dia da semana e hora de início.
 *
 * @param student_code Código do estudante para o qual imprimir o horário.
 *
 * @note Esta função utiliza a função compareLessons para ordenar as aulas.
 *
 * @note A complexidade temporal depende do número total de aulas do estudante (N) e do número de dias da semana (D).
 *       A função envolve operações de ordenação e laços que percorrem as aulas por dia da semana, resultando em uma
 *       complexidade de O(N * log(N) + D).
 */
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

/**
 * @brief Imprime o horário de um estudante, organizado por dia da semana e hora de início.
 *
 * @param student_code Código do estudante para o qual imprimir o horário.
 *
 * @note Esta função utiliza a função compareLessons para ordenar as aulas.
 *
 * @note A complexidade temporal depende do número total de aulas do estudante (N) e do número de dias da semana (D).
 *       A função envolve operações de ordenação e laços que percorrem as aulas por dia da semana, resultando em uma
 *       complexidade de O(N * log(N) + D).
 */
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

/**
 * @brief Imprime uma lista de estudantes, exibindo o nome e o número de identificação de cada um.
 *
 * @param students Lista de ponteiros para objetos do tipo Student.
 *
 * @note Esta função percorre a lista de estudantes e imprime o nome e o número de identificação de cada um.
 *
 * @note A complexidade temporal é O(N), onde N é o número de estudantes na lista.
 */
void Menu::printListStudents(list<Student*> students) {
    for(Student *student : students) {
        cout << student->get_name() << ": " << student->get_code() << "\n";
    }
}

/**
 * @brief Aguarda a entrada do usuário antes de continuar a execução.
 *
 * @note Esta função exibe uma mensagem para o usuário e espera pela entrada do teclado antes de continuar a execução.
 *
 * @note A complexidade temporal é O(1), pois a função executa um número fixo de operações, independentemente dos dados de entrada.
 */
void Menu::wait() {
    string input;
    cout << endl << "Press any key to leave"<<endl;
    cin >> input;
}

/**
 * @brief Encerra o programa, salvando as alterações e exibindo mensagens de saída.
 *
 * @note Esta função salva as alterações no arquivo e exibe mensagens indicando que as alterações estão sendo salvas e que o programa está sendo encerrado.
 *
 * @note A complexidade temporal depende da implementação específica da função de escrita no arquivo (`data_.fileWriter`). Se essa função tiver uma complexidade temporal específica, ela afetará a complexidade total da função `exitProgram`.
 */
void Menu::exitProgram() const {
    cout << endl << "Saving changes..." << endl;
    data_.fileWriter("../schedule/students_classes_updated.csv");
    cout << endl << "Exiting program..." << endl;
    exit(0);
}

/**
 * @brief Retorna o número de UCs em que um aluno está matriculado.
 *
 * @param student Ponteiro para o objeto Student.
 * @return Número de UCs em que o aluno está matriculado.
 *
 * @note Esta função percorre a lista de UCs do aluno e conta o número de UCs.
 * @note A complexidade temporal é O(n), onde n é o número de UCs em que o aluno está matriculado.
 */
int Menu::Students_Num_Ucs(Student *student){
    int count = 0;

    // Obtém a lista de UCs do aluno.
    vector<UC_Class*> uc_classes = student->get_uc_classes();

    // Percorre a lista de UCs e incrementa o contador.
    for (UC_Class *uc_class : uc_classes){
        count ++;
    }

    return count;
}

/**
 * @brief Ordena uma lista de alunos por nome em ordem ascendente.
 *
 * @param students Lista de ponteiros para objetos Student.
 *
 * @note Esta função utiliza o método sort da lista e uma lambda function para comparar os nomes dos alunos.
 * @note A complexidade temporal depende do método de ordenação utilizado pela lista, mas geralmente é O(n log n).
 */
void Menu::sortStudents_byname(list<Student*>& students) {
    students.sort([](Student* student1, Student* student2) {
        return student1->get_name() < student2->get_name();
    });
}

/**
 * @brief Ordena uma lista de alunos por nome em ordem descendente.
 *
 * @param students Lista de ponteiros para objetos Student.
 *
 * @note Esta função utiliza o método sort da lista e uma lambda function para comparar os nomes dos alunos em ordem decrescente.
 * @note A complexidade temporal depende do método de ordenação utilizado pela lista, mas geralmente é O(n log n).
 */
void Menu::sortStudents_bynameInv(list<Student*>& students) {
    students.sort([](Student* student1, Student* student2) {
        return student1->get_name() > student2->get_name();
    });
}

/**
 * @brief Ordena uma lista de alunos por código em ordem ascendente.
 *
 * @param students Lista de ponteiros para objetos Student.
 *
 * @note Esta função utiliza o método sort da lista e uma lambda function para comparar os códigos dos alunos em ordem crescente.
 * @note A complexidade temporal depende do método de ordenação utilizado pela lista, mas geralmente é O(n log n).
 */
void Menu::sortStudents_bycode(list<Student *>& students) {
    students.sort([](Student* student1, Student* student2) {
        return student1->get_code() < student2->get_code();
    });
}

/**
 * @brief Ordena uma lista de alunos por código em ordem descendente.
 *
 * @param students Lista de ponteiros para objetos Student.
 *
 * @note Esta função utiliza o método sort da lista e uma lambda function para comparar os códigos dos alunos em ordem decrescente.
 * @note A complexidade temporal depende do método de ordenação utilizado pela lista, mas geralmente é O(n log n).
 */
void Menu::sortStudents_bycodeInv(list<Student *>& students) {
    students.sort([](Student* student1, Student* student2) {
        return student1->get_code() > student2->get_code();
    });
}

/**
 * @brief Ordena uma lista de alunos por número de UCs em ordem crescente.
 *
 * @param students Lista de ponteiros para objetos Student.
 *
 * @note Esta função utiliza o método sort da lista e uma lambda function para comparar o número de UCs dos alunos em ordem crescente.
 * @note A complexidade temporal depende do método de ordenação utilizado pela lista, mas geralmente é O(n log n).
 */
void Menu::sortStudents_byNum_Uc(list<Student *>& students) {
    students.sort([this](Student* student1, Student* student2) {
        int num1 = Students_Num_Ucs(student1);
        int num2 = Students_Num_Ucs(student2);
        return num1 < num2;
    });
}

/**
 * @brief Ordena uma lista de alunos por número de UCs em ordem crescente.
 *
 * @param students Lista de ponteiros para objetos Student.
 *
 * @note Esta função utiliza o método sort da lista e uma lambda function para comparar o número de UCs dos alunos em ordem crescente.
 * @note A complexidade temporal depende do método de ordenação utilizado pela lista, mas geralmente é O(n log n).
 */
void Menu::sortStudents_byNum_UcInv(list<Student *>& students) {
    students.sort([this](Student* student1, Student* student2) {
        int num1 = Students_Num_Ucs(student1);
        int num2 = Students_Num_Ucs(student2);
        return num1 > num2;
    });
}