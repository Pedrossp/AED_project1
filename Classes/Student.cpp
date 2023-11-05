#include "Student.h"

using namespace std;


Student::Student(){
    studentName_ = "";
    studentCode_ = 0;
}

Student::Student(string& studentName, int studentCode){
    studentName_ = studentName;
    studentCode_ = studentCode;
}

string const Student::get_name(){
    return studentName_;
}

int const Student::get_code(){
    return studentCode_;
}

vector<UC_Class*> const Student::get_uc_classes(){
    return uc_Classes_;
}

void Student::set_uc_class(UC_Class* uc_Classes){
    uc_Classes_.push_back(uc_Classes);
}

void Student::rem(UC_Class* uc_class) {

    auto it = remove_if(uc_Classes_.begin(), uc_Classes_.end(),[uc_class] (UC_Class* t){ return (uc_class->get_ucCode() == t->get_ucCode()) && (uc_class->get_classCode() == t->get_classCode());});
    uc_Classes_.erase(it, uc_Classes_.end());

}

void Student::print_student() {

    cout << studentName_ << ": " << studentCode_;
}

void Student::print_ucClass_student() {

    for(UC_Class *ucClass: uc_Classes_){

        cout << "| " << ucClass->get_classCode() << " " << ucClass->get_ucCode();
    }
    cout << " |"<<endl;
}

/**
 * @brief Verifica se o estudante está matriculado em uma UC específica.
 *
 * @param ucCode O código da UC que se deseja verificar.
 * @return True se o estudante estiver matriculado na UC, caso contrário, False.
 *
 * Complexidade: O(n), onde 'n' é o número de UCs em que o estudante está matriculado.
 */
bool Student::isEnrolled(string ucCode){

    for (UC_Class *ucclasses: uc_Classes_) {
        if (ucclasses->get_ucCode() == ucCode) {
            return true;
        }
    }
    return false;
}

