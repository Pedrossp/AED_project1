#include "DataManip.h"
#include "Menu.h"

using namespace std;

int main() {
    DataManip data;
    Menu menu(data);
    menu.run();

    return 0;
}

