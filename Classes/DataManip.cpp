#include "DataManip.h"
#include "Student.h"
#include "Request.h"

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

queue<Request *> DataManip::get_pendent_requests() {
    return pendent_requests_;
}

queue<Request *> DataManip::get_denied_request() {
    return denied_requests_;
}

void DataManip::sortStudents_bycode(vector<Student *>) {
    sort(students_.begin(), students_.end(), [](Student* student1, Student* student2) {
        return student1->get_code() < student2->get_code();
    });
}

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
    UC_Class* notFound = new UC_Class("Not Found", "");
    return notFound;
}
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
    string a = "a";
    Student *stdnt = new Student(a, -1);
    return stdnt;
}

string DataManip::found_classCode_student(std::string uc_code, Student *student) {

    vector<UC_Class*> uc_classes = student->get_uc_classes();

    for (UC_Class *ucClass: uc_classes){

        if (ucClass->get_ucCode()==uc_code){

            return ucClass->get_classCode();
        }
    }
}

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
        // Remover espaços em branco ao final da palavra
        word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
        words.push_back(word);

        studentCode = stoi(words[0]);
        studentName = words[1];
        ucCode = words[2];
        classCode = words[4];
        words.clear();



        Student *stdt = found_student(studentCode);

        if (stdt->get_code() == -1){
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

void DataManip::set_denied_request(Request* request) {
    denied_requests_.push(request);
}

void DataManip::leave_ucClass(Student *student, string uc_code) {
    string class_code = found_classCode_student(uc_code, student);
    UC_Class *uc_class = new UC_Class(uc_code, class_code);
    vector<UC_Class *> ucClasses = uc_classes_;

    for (UC_Class *ucClass: ucClasses){

        if (ucClass->get_ucCode() == uc_class->get_ucCode() && ucClass->get_classCode() == uc_class->get_classCode()){
            student->rem(ucClass);
        }
    }
    cout << "Remove complete..." << endl;
}

void DataManip::join_new_ucClass(Student *student, string uc_code, string class_code) {

    UC_Class *uc_class = found_ucclass(uc_code, class_code);
    int i = consultClasss_UcOcupation(uc_class);
    int count = student->get_uc_classes().size();

    if (count >= 7){
        cout << "Not possible to join, already in 7 UC..." << endl;

    }

    else if ( i >= 26){
        cout << "This UC is full..." << endl;
    }

    else{
        student->set_uc_class(uc_class);
        cout << "Join complete...";
    }
}

void DataManip::switch_class(Student *student, string uc_code, string final_class_code) { //fazerrrrr

    string initial_class_code = found_classCode_student(uc_code, student);
    UC_Class *uc_class_initial= found_ucclass(uc_code,initial_class_code);
    UC_Class *uc_class_final = found_ucclass(uc_code, final_class_code);
    int n_final = consultClasss_UcOcupation(uc_class_final);
    int n_initial = consultClasss_UcOcupation(uc_class_initial);

    if (n_final >= 26){

        cout << "This UC is full..." << endl;
    }

    else if ( n_final < n_initial ){
        if (!sobreposiçao_horarios()){

            student->rem(uc_class_initial);
            student->set_uc_class(uc_class_final);
        }
        else{
            cout << "Sobreposiçao horarios";
        }
    }

    else{
        if ((n_final - n_initial) <= 4){
            if (!sobreposiçao_horarios()){

                student->rem(uc_class_initial);
                student->set_uc_class(uc_class_final);
            }
            else{
                cout << "Sobreposiçao horarios";
            }
        }

    }
}

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

int DataManip::consultClasss_UcOcupation(UC_Class *ucClass) {

    vector<Student *> students = students_;
    int count = 0;

    for (Student *student: students){

        vector<UC_Class *> uc_classes = student->get_uc_classes();

        for (UC_Class *uc_class: uc_classes){

            if(uc_class->get_classCode() == ucClass->get_classCode() && uc_class->get_ucCode() == ucClass->get_ucCode()){
                count++;

            }
        }
    }
}