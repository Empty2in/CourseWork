#include "TestFunc.h"
#include "DoubleList.h"

int main() {
    try {
        mainMenu();
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what();
        exit(-1);
    }
    return 0;
}