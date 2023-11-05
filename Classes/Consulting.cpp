//
// Created by edu on 31-10-2023.
//
#include <iostream>

#include "Consulting.h"
#include "DataManip.h"
#include "UC_Class.h"

using namespace std;


Consulting::Consulting(DataManip data) {
    data_=data;
}

/**
 * @brief Consulta o horário de um estudante.
 *
 * Esta função consulta e retorna o horário de um estudante com base no seu código. O horário inclui todas as aulas do estudante, organizadas por UC (Unidade Curricular) e turma, bem como as informações de código de UC e código de turma correspondentes.
 *
 * @param student_code O código do estudante para o qual o horário será consultado.
 * @return Um vetor de pares contendo as aulas do estudante e informações de código de UC e código de turma correspondentes.
 *
 * @complexity A complexidade de tempo desta função depende do número de UCs e turmas nas quais o estudante está matriculado, bem como do número de aulas associadas a essas UCs e turmas. Portanto, a complexidade de tempo média é proporcional ao número total de aulas do estudante, ou seja, O(k), onde 'k' é o número total de aulas.
 */
vector<pair<vector<Lesson *>, pair<string,string>>> Consulting::consultStudentSchedule(int student_code) {

    Student *student = data_.found_student(student_code);

    vector<Lesson*> lessons_;
    vector<UC_Class*> ucClasses = student->get_uc_classes();
    vector<pair<vector<Lesson *>, pair<string,string>>> lessons_uc;

    for(UC_Class *uc_class: ucClasses){

        vector<Lesson*> lessons = uc_class->get_lessons();

        for(Lesson *lesson: lessons){

            lessons_.push_back(lesson);
        }
        lessons_uc.push_back({lessons ,{uc_class->get_ucCode(),uc_class->get_classCode()}});
        lessons_.clear();
    }
    return lessons_uc;
}

/**
 * @brief Consulta o horário de uma turma.
 *
 * Esta função consulta e retorna o horário de uma turma com base no código da turma. O horário inclui todas as aulas da turma, organizadas por UC (Unidade Curricular) e turma, bem como as informações de código de UC e código de turma correspondentes.
 *
 * @param class_code O código da turma para a qual o horário será consultado.
 * @return Um vetor de pares contendo as aulas da turma e informações de código de UC e código de turma correspondentes.
 *
 * @complexity A complexidade de tempo desta função depende do número total de UCs na lista de UCs e do número total de aulas associadas a essas UCs. Portanto, a complexidade de tempo média é proporcional ao número total de aulas da turma, ou seja, O(k), onde 'k' é o número total de aulas da turma.
 */
vector<pair<vector<Lesson *>, pair<string,string>>> Consulting::consultClassSchedule(string class_code) {

    vector<UC_Class *> uc_classes = data_.get_uc_classes();
    vector<pair<vector<Lesson *>, pair<string,string>>> lessons_uc;
    vector<Lesson *> lessons;


    for(UC_Class *ucClass: uc_classes){

        if(ucClass->get_classCode()==class_code){

            for(Lesson *lesson: ucClass->get_lessons()){
                lessons.push_back(lesson);
            }

            lessons_uc.push_back({lessons ,{ucClass->get_ucCode(),ucClass->get_classCode()}});
            lessons.clear();
        }
    }

    return lessons_uc;
}

/**
 * @brief Consulta os alunos matriculados em uma turma.
 *
 * Esta função consulta e retorna a lista de alunos matriculados em uma turma com base no código da turma. A função percorre a lista de alunos, verificando para cada aluno se ele está matriculado na turma especificada e, em caso afirmativo, o adiciona à lista de alunos consultados.
 *
 * @param class_code O código da turma para a qual os alunos serão consultados.
 * @return Uma lista de ponteiros para objetos Student representando os alunos matriculados na turma.
 *
 * @complexity A complexidade de tempo desta função depende do número total de alunos na lista de alunos e do número total de UCs associadas a cada aluno. Portanto, a complexidade de tempo média é proporcional ao produto do número total de alunos e o número médio de UCs matriculadas por aluno, ou seja, O(n * m), onde 'n' é o número total de alunos e 'm' é o número médio de UCs matriculadas por aluno.
 */
list<Student *> Consulting::consultStudentClass(string class_code) {

    list<Student *> consult_students;
    vector<Student *> students = data_.get_students();

    for (Student *student: students){

        vector<UC_Class *> uc_classes = student->get_uc_classes();

        for (UC_Class *uc_class: uc_classes){

            if (uc_class->get_classCode() == class_code){

                consult_students.push_back(student);
                break;
            }
        }
    }

    return consult_students;
}

/**
 * @brief Consulta os alunos matriculados em uma UC.
 *
 * Esta função consulta e retorna a lista de alunos matriculados em uma Unidade Curricular (UC) com base no código da UC. A função percorre a lista de alunos, verificando para cada aluno se ele está matriculado em alguma turma associada à UC especificada e, em caso afirmativo, o adiciona à lista de alunos consultados.
 *
 * @param uc_code O código da UC para a qual os alunos serão consultados.
 * @return Uma lista de ponteiros para objetos Student representando os alunos matriculados na UC.
 *
 * @complexity A complexidade de tempo desta função depende do número total de alunos na lista de alunos (`n`) e do número total de UCs associadas a cada aluno (o que pode variar para diferentes alunos). Portanto, a complexidade de tempo média é proporcional ao produto do número total de alunos e o número médio de UCs matriculadas por aluno (`n * m`).
 */
list<Student *> Consulting::consultStudentUc(string uc_code) {

    list<Student *> consult_students;
    vector<Student *> students = data_.get_students();

    for (Student *student: students){

        vector<UC_Class *> uc_classes = student->get_uc_classes();

        for (UC_Class *uc_class: uc_classes){

            if (uc_class->get_ucCode() == uc_code){

                consult_students.push_back(student);
                break;
            }
        }
    }

    return consult_students;
}

/**
 * @brief Consulta os alunos matriculados em turmas de um determinado ano.
 *
 * Esta função consulta e retorna a lista de alunos matriculados em turmas de um ano específico, com base no caractere que representa o ano. A função percorre a lista de alunos, verificando para cada aluno se ele está matriculado em alguma turma cujo código de turma começa com o caractere do ano especificado e, em caso afirmativo, o adiciona à lista de alunos consultados.
 *
 * @param year O caractere que representa o ano a ser consultado.
 * @return Uma lista de ponteiros para objetos Student representando os alunos matriculados em turmas do ano especificado.
 *
 * @complexity A complexidade de tempo desta função depende do número total de alunos na lista de alunos (`n`) e do número total de turmas associadas a cada aluno (o que pode variar para diferentes alunos). Portanto, a complexidade de tempo média é proporcional ao produto do número total de alunos e o número médio de turmas matriculadas por aluno (`n * m`).
 */
list<Student *> Consulting::consultStudentYear(char year) {

    list<Student *> consult_students;
    vector<Student *> students = data_.get_students();

    for (Student *student: students) {

        vector<UC_Class *> uc_classes = student->get_uc_classes();

        for (UC_Class *uc_class: uc_classes){

            if (uc_class->get_classCode()[0] == year){

                consult_students.push_back(student);
                break;
            }
        }
    }

    return consult_students;
}

/**
 * @brief Consulta o número de alunos matriculados em pelo menos n turmas.
 *
 * Esta função consulta e retorna o número de alunos que estão matriculados em pelo menos `n` turmas. A função percorre a lista de alunos, contando o número de turmas em que cada aluno está matriculado e, se esse número for maior ou igual a `n`, incrementa o contador de resultados.
 *
 * @param n O número mínimo de turmas em que um aluno deve estar matriculado para ser contado.
 * @return O número de alunos matriculados em pelo menos `n` turmas.
 *
 * @complexity A complexidade de tempo desta função é proporcional ao número total de alunos na lista de alunos (`n`) multiplicado pelo número médio de turmas matriculadas por aluno (`m`). Portanto, a complexidade de tempo média é aproximadamente `O(n * m)`.
 */
int Consulting::consultStudentsEnrolled(int n) {

    vector<Student *> students = data_.get_students();
    int result = 0;

    for (Student *student: students){

        vector<UC_Class *> uc_classes = student->get_uc_classes();
        int count = 0;

        for (UC_Class *uc_class: uc_classes){

            count++;
        }

        if (count >= n){
            result++;
        }
    }

    return result;
}

/**
 * @brief Consulta a unidade curricular com o maior número de matrículas.
 *
 * Esta função calcula e retorna a unidade curricular (UC) com o maior número de matrículas, contando quantas vezes cada UC aparece nas matrículas dos alunos. No entanto, esta função não é chamada ou usada em outras partes do programa principal.
 * @note Esta função nao foi utilizada porque não achamos relevante para o programa.
 * @complexity A complexidade desta função é O(N * M), onde N é o número de estudantes e M é o número médio de UCs em que cada estudante está matriculado.
 * @return A unidade curricular (UC) com o maior número de matrículas.
 */
string Consulting::consultMaxUc() {

    vector<Student *> students = data_.get_students();
    map<string, int> consult;

    for (Student *student: students){

        vector<UC_Class *> uc_classes = student->get_uc_classes();

        for (UC_Class *uc_class: uc_classes){

            consult[uc_class->get_ucCode()]++;
        }
    }
    int max = 0;
    string max_uc = "";

    for (const auto& par : consult){

        if(par.second > max){

            max = par.second;
            max_uc = par.first;
        }
    }

    return max_uc;
}
