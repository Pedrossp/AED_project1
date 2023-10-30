#include "DataManip.h"
#include "Student.h"

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

void DataManip::sortStudents_bycode(vector<Student *>) {
    sort(students_.begin(), students_.end(), [](Student* student1, Student* student2) {
        return student1->get_code() < student2->get_code();
    });
}
UC_Class *DataManip::found_ucclass(UC_Class *ucClass){
    int size = uc_classes_.size();
    int low =0;
    int high =size -1;

    while (low <= high){
        int mid = low + (high - low) / 2;

        if(uc_classes_[mid]->get_classCode() == ucClass->get_classCode() && uc_classes_[mid]->get_ucCode() == ucClass->get_ucCode() ){
            return uc_classes_[mid];
        }
        else if (uc_classes_[mid]->get_ucCode() < ucClass->get_ucCode() ||
                 (uc_classes_[mid]->get_ucCode() == ucClass->get_ucCode() &&
                  uc_classes_[mid]->get_classCode() < ucClass->get_classCode())){
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

void DataManip::read_classes_per_uc(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        return; // Sair da função em caso de erro
    }

    string line, ucCode, classCode;

    getline(file, line);
    while (getline(file, line)) {
        stringstream iss(line);
        string word;
        vector<string> words;

        while (getline(iss, word, ',')) {
            words.push_back(word);
        }

        classCode = words[0];
        ucCode = words[1];

        UC_Class *uc = new UC_Class(ucCode, classCode);
        uc_classes_.push_back(uc);

    }
}

void DataManip::read_classes(string filename) {
    string line, classCode, ucCode, weekDay, type;
    double startHour, duration;


    ifstream file(filename);
    getline(file, line);

    while(getline(file, line)){

        stringstream iss(line);
        string word;
        vector<string> words;

        while(getline(iss, word, ',')){
            words.push_back(word);
        }

        classCode = words[0];
        ucCode = words[1];
        weekDay = words[2];
        startHour = stof(words[3]);
        duration = stof(words[4]);
        type = words[5];
        words.clear();


            //por acabar
    }
}

void DataManip::read_students_classes(string filename) {
    string line ,studentName, ucCode, classCode;
    int studentCode;
    ifstream file(filename);
    getline(file, filename);

    while(getline(file, line)){
        stringstream iss(line);
        string word;
        vector<string>words;

        while(getline(iss, word, ',')){
            words.push_back(word);
        }

        studentCode = stoi(words[0]);
        studentName = words[1];
        ucCode = words[2];
        classCode = words[3];
        // wait-------------------------------------------------------

        Student *test = found_student(studentCode);

        if (test->get_code() == -1){
            UC_Class *uc_class = new UC_Class(ucCode, classCode);

        }

        //wait--------------------------------------------------------
        Student *student = new Student(studentName, studentCode);
        students_.push_back(student);

        //por acabar

    }
    sortStudents_bycode(students_);
}



