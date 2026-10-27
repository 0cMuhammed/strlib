#include "MyString.h"
#include <iostream>

void printResult(const char* testName, size_t actual, size_t expected) {
    std::cout << testName << ": ";
    if (actual == expected) {
        std::cout << "PASS (got " << actual << ")\n";
    }
    else {
        std::cout << "FAIL (got " << actual << ", expected " << expected << ")\n";
    }
}

int main() {
   
    MyString a = "ABCXYZ";
  

    std::cout << a.rfind("");

    return 0;
}