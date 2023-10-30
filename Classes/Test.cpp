//
// Created by edu on 30-10-2023.
//

#include <iostream>
#include "Test.h"
#include "DataManip.h"

Test::Test() {
    x_= 0;
}
void Test::test1() {
    DataManip data;
    data.read_classes_per_uc("../schedule/classes.csv");
    vector<UC_Class *> uc = data.get_uc_classes();

    for (UC_Class*a : uc) {

        std::cout<<a->get_ucCode() <<" "<<a->get_classCode()<<"\n";

    }
}