#include "DataManip.h"
#include "Student.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

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

void DataManip::read_classes_per_uc(string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        return; // Sair da função em caso de erro
    }


    string line, ucCode, classCode;


    getline(file, line);
    cout<<"Hello";
    while (getline(file, line)) {
        std::cout<<"ola";
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

void DataManip::read_students_classes(string filename) {

}

vector<UC_Class*> DataManip::get_uc_classes(){
    return uc_classes_;
}
