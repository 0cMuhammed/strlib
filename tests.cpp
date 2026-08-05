#include "MyString.h"
#include <iostream>

void printResult(const std::string& testName, bool passed) {
    std::cout << (passed ? "[PASS] " : "[FAIL] ") << testName << std::endl;
}

int main() {

    MyString s1("Hello World");
    s1.erase(5, 6); // remove " World"
    printResult("erase(5, 6) middle", s1 == MyString("Hello"));

    // erase from the start
    MyString s2("Hello World");
    s2.erase(0, 6); // remove "Hello "
    printResult("erase(0, 6) from start", s2 == MyString("World"));

    // len bigger than what's left, should just erase to the end
    MyString s3("Hello World");
    s3.erase(5, 1000);
    printResult("erase(5, 1000) clamps to end", s3 == MyString("Hello"));

    // single-arg erase, erases from pos to the end
    MyString s4("Hello World");
    s4.erase(5);
    printResult("erase(5) to end", s4 == MyString("Hello"));

    // default erase, clears everything
    MyString s5("Hello World");
    s5.erase();
    printResult("erase() clears all", s5.empty());

    // pos out of range should throw
    MyString s6("Hello");
    bool threw = false;
    try {
        s6.erase(10, 1);
    }
    catch (const std::out_of_range&) {
        threw = true;
    }
    printResult("erase(10, 1) throws out_of_range", threw);
    return 0;
}