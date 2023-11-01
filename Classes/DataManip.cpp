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






