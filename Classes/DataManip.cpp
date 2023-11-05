#include "DataManip.h"
#include "Student.h"
#include "Request.h"
#include "Consulting.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>


using namespace std;


vector<UC_Class*> DataManip::get_uc_classes(){
    return uc_classes_;
}

vector<Student *> DataManip::get_students() {
    return students_;
}

/**
 * @brief Ordena os estudantes pelo seu código de estudante em ordem crescente.
 * @param students Um vetor de ponteiros para objetos Student que deve ser ordenado.
 * @complexity A complexidade de tempo é O(n log n), onde 'n' é o número de estudantes no vetor.
 */
void DataManip::sortStudents_bycode(vector<Student *>) {
    sort(students_.begin(), students_.end(), [](Student* student1, Student* student2) {
        return student1->get_code() < student2->get_code();
    });
}
/**
 * @brief Encontra uma classe de UC com base no código de UC e no código da classe.
 * @param uc_code O código de UC a ser pesquisado.
 * @param class_code O código da classe a ser pesquisado.
 * @return Um ponteiro para a classe de UC encontrada ou nullptr se não for encontrada.
 *
 * A função realiza uma pesquisa binária no vetor de classes de UC para encontrar uma classe de UC
 * com os códigos de UC e classe fornecidos. Se uma classe correspondente for encontrada, um ponteiro para
 * a classe de UC é retornado; caso contrário, retorna nullptr.
 *
 * @complexity A complexidade de tempo é O(log n), onde 'n' é o número de classes de UC no vetor.
 */

UC_Class *DataManip::found_ucclass(string uc_code, string class_code){
    int size = uc_classes_.size();
    int low =0;
    int high =size -1;

    while (low <= high){
        int mid = low + (high - low) / 2;

        if(uc_classes_[mid]->get_classCode() == class_code && uc_classes_[mid]->get_ucCode() == uc_code){
            return uc_classes_[mid];
        }
        else if (uc_classes_[mid]->get_ucCode() < uc_code ||
                 (uc_classes_[mid]->get_ucCode() == uc_code &&
                  uc_classes_[mid]->get_classCode() < class_code)){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }

    return nullptr;
}

/**
 * @brief Encontra um estudante com base no código do estudante.
 * @param student_code O código do estudante a ser pesquisado.
 * @return Um ponteiro para o estudante encontrado ou nullptr se não for encontrado.
 *
 * A função realiza uma pesquisa binária no vetor de estudantes para encontrar um estudante com o código fornecido.
 * Se um estudante correspondente for encontrado, um ponteiro para o estudante é retornado; caso contrário, retorna nullptr.
 *
 * @complexity A complexidade de tempo é O(log n), onde 'n' é o número de estudantes no vetor.
 */

Student *DataManip::found_student(int student_code) {
    int size = students_.size();
    int low = 0;
    int high = size - 1;

    while (low <= high){
        int mid = low + (high - low) / 2;

        if(students_[mid]->get_code() == student_code){
            return students_[mid];

        }
        else if (students_[mid]->get_code() < student_code){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return nullptr;
}

/**
 * @brief Verifica se um código de classe existe no vetor de classes de UC.
 * @param class_code O código da classe a ser verificado.
 * @return True se o código de classe for encontrado, False caso contrário.
 *
 * A função percorre o vetor de classes de UC e verifica se algum deles tem o código de classe fornecido.
 * Retorna True se um código de classe correspondente for encontrado e False se nenhum for encontrado.
 *
 * @complexity A complexidade de tempo é O(n), onde 'n' é o número de classes de UC no vetor.
 */
bool DataManip::found_if_class_code(string class_code){

    for (UC_Class* ucClass: uc_classes_){
        if (ucClass->get_classCode()==class_code){
            return true;
        }
    }
    return false;
}

/**
 * @brief Verifica se um código de UC existe no vetor de classes de UC.
 * @param uc_code O código da UC a ser verificado.
 * @return True se o código de UC for encontrado, False caso contrário.
 *
 * A função realiza uma pesquisa binária no vetor de classes de UC para verificar se um código de UC correspondente é encontrado.
 * Retorna True se um código de UC correspondente for encontrado e False se nenhum for encontrado.
 *
 * @complexity A complexidade de tempo é O(log n), onde 'n' é o número de classes de UC no vetor.
 */
bool DataManip::found_if_uc_code(string uc_code){

    int size = uc_classes_.size();
    int low =0;
    int high =size -1;

    while (low <= high){
        int mid = low + (high - low) / 2;

        if(uc_classes_[mid]->get_ucCode() == uc_code){
            return true;
        }
        else if (uc_classes_[mid]->get_ucCode() < uc_code){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return false;
}

/**
 * @brief Encontra o código da classe de UC de um estudante para uma UC específica.
 * @param uc_code O código da UC para a qual se deseja encontrar a classe.
 * @param student O estudante para o qual se deseja encontrar o código da classe.
 * @return O código da classe de UC correspondente à UC especificada e ao estudante, ou uma string vazia se não for encontrado.
 *
 * A função percorre as classes de UC de um estudante e verifica se alguma delas corresponde à UC especificada pelo código. Se uma correspondência for encontrada, o código da classe de UC é retornado. Caso contrário, uma string vazia é retornada.
 *
 * @complexity A complexidade de tempo é O(n), onde 'n' é o número de classes de UC do estudante para as quais é verificada a correspondência.
 */
string DataManip::found_classCode_student(string uc_code, Student* student) {

    vector<UC_Class*> uc_classes = student->get_uc_classes();

    for (UC_Class *ucClass: uc_classes){
        if (ucClass->get_ucCode()==uc_code){

            return ucClass->get_classCode();
        }
    }
}

/**
 * @brief Lê e processa as informações de classes por UC a partir de um arquivo.
 * @param filename O nome do arquivo que contém as informações.
 *
 * Esta função lê as informações das classes de UC (Código da UC e Código da Classe) a partir de um arquivo,
 * cria objetos UC_Class correspondentes e os armazena no vetor 'uc_classes_'.
 *
 * @param n O número de linhas no arquivo de entrada, excluindo a primeira linha de cabeçalho.
 * @complexity A complexidade de tempo é O(n), onde 'n' é o número de linhas no arquivo de entrada.
 */
void DataManip::read_classes_per_uc(string filename) {

    string line, ucCode, classCode;

    ifstream file(filename);
    getline(file, line);

    while (getline(file, line)) {

        replace(line.begin(), line.end(), ',', ' ');

        stringstream iss(line);
        string word;
        vector<string> words;

        while (iss >> word){
            words.push_back(word);

        }

        ucCode = words[0];
        classCode = words[1];


        UC_Class *uc = new UC_Class(ucCode, classCode);
        uc_classes_.push_back(uc);

    }
}

void DataManip::read_classes(string filename) {

    string line, classCode, ucCode, weekDay, type;
    float startHour, duration;


    ifstream file(filename);
    getline(file, line);

    while(getline(file, line)){

        replace(line.begin(), line.end(), ',', ' ');

        stringstream iss(line);
        string word;
        vector<string> words;

        while(iss >> word){

            words.push_back(word);
        }

        classCode = words[0];
        ucCode = words[1];
        weekDay = words[2];
        startHour = stof(words[3]);
        duration = stof(words[4]);
        type = words[5];
        words.clear();

        UC_Class *uccl = found_ucclass(ucCode,classCode);
        Lesson *ls = new Lesson(weekDay, startHour, duration, type);
        uccl->set_lessons(ls);

        }
}

/**
 * @brief Lê e processa as informações das aulas a partir de um arquivo.
 * @param filename O nome do arquivo que contém as informações.
 *
 * Esta função lê as informações das aulas (Código da Classe, Código da UC, Dia da Semana, Hora de Início, Duração e Tipo)
 * a partir de um arquivo, cria objetos Lesson correspondentes e os associa às UC_Classes existentes no vetor 'uc_classes_'.
 *
 * @param n O número de linhas no arquivo de entrada, excluindo a primeira linha de cabeçalho.
 * @complexity A complexidade de tempo é O(n), onde 'n' é o número de linhas no arquivo de entrada.
 */
void DataManip::read_students_classes(string filename) {

    string line ,studentName, ucCode, classCode;
    int studentCode;
    vector<string>words;

    ifstream file(filename);
    getline(file, line);

    while(getline(file, line)){


        stringstream iss(line);
        string word;

        while(getline(iss, word, ',')){
            words.push_back(word);
        }

        iss >> word;
        word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
        words.push_back(word);

        studentCode = stoi(words[0]);
        studentName = words[1];
        ucCode = words[2];
        classCode = words[4];
        words.clear();



        Student *stdt = found_student(studentCode);

        if ( found_student(studentCode) == nullptr){
            Student *student = new Student(studentName, studentCode);
            student->set_uc_class(found_ucclass(ucCode,classCode));
            students_.push_back(student);
            sortStudents_bycode(students_);

        }
        else{
            stdt->set_uc_class(found_ucclass(ucCode,classCode));
        }
    }
}

void DataManip::set_pendent_requests(Request* request) {
    pendent_requests_.push(request);
}

/**
 * @brief Processa uma solicitação para sair de uma UC_Class.
 * @param student Um ponteiro para o objeto Student que deseja sair.
 * @param uc_code O código da UC da qual o aluno deseja sair.
 *
 * Esta função processa uma solicitação para que um aluno saia de uma UC_Class específica. O aluno é removido da UC_Class correspondente.
 *
 * @param n O número de UC_Classes no vetor 'uc_classes_'.
 * @complexity A complexidade de tempo é O(n), onde 'n' é o número de UC_Classes no vetor 'uc_classes_'.
 */
void DataManip::leave_ucClass(Student *student, string uc_code) {
    cout << "Leave request" << endl;
    string class_code = found_classCode_student(uc_code, student);
    vector<UC_Class *> ucClasses = uc_classes_;

    for (UC_Class *ucClass: ucClasses){

        if (ucClass->get_ucCode() == uc_code && ucClass->get_classCode() == class_code){
            student->rem(ucClass);
        }
    }
    cout << "The student " << student->get_name() << " is no longer enrolled in this UC (" << uc_code << ")..." << endl;
}

void DataManip::join_new_ucClass(int student_code, string uc_code_final, string final_class_code) {

    cout << "Join request:" << endl;
    Student *student1 = found_student(student_code);
    UC_Class *uc_class_final = found_ucclass(uc_code_final, final_class_code);

    int i = consultClass_UcOcupation(uc_code_final, final_class_code);
    int count = student1->get_uc_classes().size();

    if (count >= 7){
        cout << "The student " << student1->get_name() << " can not join a new UC, already in 7..." << endl;

    }

    else if(timetable_overlap(student1, uc_class_final)){
        cout << "The student's schedule " << student1->get_name() << " is not compatible with the schedule of this UC (" << uc_code_final << " ," << final_class_code << ")..." << endl;
    }

    else if ( i >= 26){
        cout << "The student " << student1->get_name() << " can not join in this class, because it is full..." << endl;
    }

    else{
        student1->set_uc_class(uc_class_final);
        cout << "The student " << student1->get_name() << " is now in this class (" << final_class_code << ")" <<" at this UC (" << uc_code_final << ")..." << endl;
    }
}

/**
 * @brief Processa uma solicitação para ingressar em uma nova UC_Class.
 * @param student_code O código do aluno que deseja ingressar na UC_Class.
 * @param uc_code_final O código da UC da qual o aluno deseja ingressar.
 * @param final_class_code O código da classe da UC na qual o aluno deseja ingressar.
 *
 * Esta função processa uma solicitação para que um aluno ingresse em uma nova UC_Class específica, desde que as condições sejam atendidas. O aluno só pode ingressar em uma nova UC_Class se ele ainda não estiver matriculado em 7 UC_Classes, se o horário da UC_Class não entrar em conflito com o horário do aluno e se a capacidade da UC_Class não estiver cheia.
 *
 * @param n O número de UC_Classes no vetor 'uc_classes_'.
 * @param m O número de aulas na UC_Class especificada.
 * @complexity A complexidade de tempo é O(n) devido à busca por UC_Classes no vetor 'uc_classes_', onde 'n' é o número de UC_Classes. A complexidade total depende da função 'timetable_overlap', que pode ser O(m * n), onde 'm' é o número de aulas na UC_Class.
 */
void DataManip::switch_class(Student *student, string uc_code, string final_class_code) {
    cout << "Switch request:" << endl;
    string initial_class_code = found_classCode_student(uc_code, student);
    UC_Class *uc_class_initial= found_ucclass(uc_code,initial_class_code);
    UC_Class *uc_class_final = found_ucclass(uc_code, final_class_code);
    int n_final = consultClass_UcOcupation(uc_code, final_class_code);
    int n_initial = consultClass_UcOcupation(uc_code, initial_class_code);

    if (n_final >= 26){
        cout << "The student " << student->get_name() << " can not switch to this class (" << final_class_code << "), because it is full..." << endl;

    }


    else if ( n_final < n_initial ){
        student->rem(uc_class_initial);
        if (!timetable_overlap(student, uc_class_final)){
            student->set_uc_class(uc_class_final);
            cout << "The student " << student->get_name() << " is now in this class (" << final_class_code << ")" <<" at this UC (" << uc_code << ")..." << endl;
        }

        else{
            student->set_uc_class(uc_class_initial);
            cout << "The student's schedule " << student->get_name() << " is not compatible with the schedule of this class (" << final_class_code << ")..." << endl;

        }
    }

    else{
        if ((n_final - n_initial) <= 4){
            student->rem(uc_class_initial);
            if (!timetable_overlap(student, uc_class_final)){
                student->set_uc_class(uc_class_final);
                cout << "The student " << student->get_name() << " is now in this class (" << final_class_code << ")" <<" at this UC (" << uc_code << ")..." << endl;
            }

            else{
                student->set_uc_class(uc_class_final);
                cout << "The student's schedule " << student->get_name() << " is not compatible with the schedule of this class (" << final_class_code << ")..." << endl;

            }
        }
        else{
            cout << "The student " << student->get_name() << " can not switch to this class (" << final_class_code << "), because the change causes imbalance..." << endl;
        }

    }
}

/**
 * @brief Escreve dados dos alunos e suas matrículas em UC_Classes em um arquivo CSV.
 * @param filename O nome do arquivo no qual os dados serão escritos.
 *
 * Esta função escreve os dados dos alunos, incluindo seus códigos, nomes, códigos de UC e códigos de classe de UC em um arquivo CSV especificado. Cada linha do arquivo representa um aluno matriculado em uma UC_Class.
 *
 * @param n O número de alunos no vetor 'students_'.
 * @param m A média do número de UC_Classes que cada aluno está matriculado.
 * @complexity A complexidade de tempo é O(n * m), onde 'n' é o número de alunos e 'm' é a média do número de UC_Classes que cada aluno está matriculado.
 */
void DataManip::fileWriter(string filename)const{
    ofstream out(filename);

    if (out.is_open()){
        out << "StudentCode,StudentName,UcCode,ClassCode" <<endl;

        for(Student *student: students_){

            vector<UC_Class*> uc_classes = student->get_uc_classes();

            for (UC_Class *ucClass: uc_classes){

                out << student->get_code() << "," << student->get_name() << "," << ucClass->get_ucCode() << "," << ucClass->get_classCode() << endl;

            }
        }
    }
    else {
        cout << "file not found" <<endl;
    }

}
/**
 * @brief Consulta a ocupação de uma classe UC específica.
 * @param uc_code O código da UC à qual a classe pertence.
 * @param class_code O código da classe UC a ser consultada.
 * @return O número de alunos matriculados na classe UC especificada.
 *
 * Esta função consulta o número de alunos matriculados em uma classe UC específica com base nos códigos da UC e da classe UC fornecidos. Ela percorre a lista de alunos e suas matrículas em UC_Classes para contar o número de ocorrências em que a classe UC tem o código especificado.
 *
 * @param n O número total de alunos no vetor 'students_'.
 * @param m A média do número de matrrículas de UC_Classes por aluno.
 * @complexity A complexidade de tempo é O(n * m), onde 'n' é o número total de alunos e 'm' é a média do número de matrículas de UC_Classes por aluno.
 */
int DataManip::consultClass_UcOcupation(string uc_code, string class_code) { //corrigir

    vector<Student *> students = students_;
    int count = 0;

    for (Student *student: students){

        vector<UC_Class *> uc_classes = student->get_uc_classes();

        for (UC_Class *uc_class: uc_classes){

            if(uc_class->get_classCode() == class_code && uc_class->get_ucCode() == uc_code){
                count++;

            }
        }
    }
    return count;
}

/**
 * @brief Verifica se há sobreposição de horários para um aluno em relação a uma classe UC final.
 * @param student O aluno para o qual verificar a sobreposição de horários.
 * @param uc_class_final A classe UC final que deseja verificar se tem sobreposição de horários com o aluno.
 * @return Verdadeiro se houver sobreposição de horários, falso caso contrário.
 *
 * Esta função verifica se há sobreposição de horários entre a classe UC final e todas as classes UC nas quais o aluno está matriculado. Ela compara os horários das aulas e os dias da semana. Se encontrar qualquer sobreposição, retorna verdadeiro, caso contrário, retorna falso.
 *
 * @param n O número total de aulas na classe UC final.
 * @param m O número total de classes UC em que o aluno está matriculado.
 * @param p A média do número de aulas por classe UC.
 * @complexity A complexidade de tempo é O(n * m * p), onde 'n' é o número total de aulas na classe UC final, 'm' é o número total de classes UC em que o aluno está matriculado e 'p' é a média do número de aulas por classe UC.
 */
bool DataManip::timetable_overlap(Student *student, UC_Class *uc_class_final) {

    vector<Lesson*> lessons_final = uc_class_final->get_lessons();
    vector<UC_Class*> uc_classes = student->get_uc_classes();

    for (UC_Class *ucClass: uc_classes){

        vector<Lesson*> lessons = ucClass->get_lessons();

        for (Lesson *lesson: lessons){

            for (Lesson *lesson_final: lessons_final){

                if (lesson->get_weekday() == lesson_final->get_weekday() && (lesson->get_starthour() < lesson_final->get_endhour()  && lesson->get_endhour() > lesson_final->get_starthour())){

                    return true;

                }
            }
        }
    }
    return false;

}

/**
 * @brief Processa as solicitações pendentes dos alunos.
 *
 * Esta função processa as solicitações pendentes na fila de solicitações. Cada solicitação é verificada e tratada com base no seu tipo. Para solicitações do tipo "switch," "join" e "leave," a função chama os métodos correspondentes (e.g., switch_class, join_new_ucClass, leave_ucClass) para efetuar as mudanças apropriadas no registro de matrícula do aluno.
 *
 * @complexity A complexidade de tempo depende do número de solicitações pendentes na fila e das operações executadas para cada solicitação. Se houver 'n' solicitações pendentes na fila, a complexidade de tempo pode ser aproximadamente O(n), uma vez que a função processa cada solicitação uma vez.
 */
void DataManip::process_pendent_requests() {

    while(!pendent_requests_.empty()){
        Request *request = pendent_requests_.front();

        if (request->get_type() == "switch"){
            Student *student = found_student(request->get_student().get_code());
            switch_class(student, request->get_uc_code(), request->get_class_code());
            pendent_requests_.pop();
        }

        else if (request->get_type() == "join"){
            Student *student = found_student(request->get_student().get_code());
            join_new_ucClass(student->get_code(), request->get_uc_code(), request->get_class_code());
            pendent_requests_.pop();
        }

        else if (request->get_type() == "leave"){
            Student *student = found_student(request->get_student().get_code());
            leave_ucClass(student, request->get_uc_code());
            pendent_requests_.pop();
        }
    }
}

/**
 * @brief Exibe as solicitações pendentes na fila.
 *
 * Esta função exibe as solicitações pendentes na fila de solicitações. Para cada solicitação, mostra informações como o número do aluno, o tipo de solicitação (join, switch, leave), o código da UC e o código da turma, fornecendo uma visão geral das solicitações pendentes.
 *
 * @complexity A complexidade de tempo desta função é O(n), onde 'n' é o número de solicitações pendentes na fila. A função itera sobre cada solicitação na fila uma vez para exibir suas informações.
 */
void DataManip::ShowPendingRequests() {
    queue<Request*> copyQueue = pendent_requests_;
    cout << "Pending requests: " <<endl;

    while(!copyQueue.empty()){

        Request *request = copyQueue.front();
        cout << "Student nº " << request->get_student().get_code()
        << " has a request to " ;

        if(request->get_type()== "join"){
            cout << "join the uc " << request->get_uc_code() << " in the class " << request->get_class_code()<<"."<< endl;
        }

        else if (request->get_type()== "switch"){
            cout<< "switch to class " << request->get_class_code() << " in the uc " << request->get_uc_code()<<"." << endl;
        }

        else if (request->get_type()=="leave"){
            cout << "leave this uc " << request->get_uc_code() <<"." <<endl;
        }

        copyQueue.pop();
    }
}

