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
    MyString s = "hello world";

    // find(MyString)
    printResult("find(\"world\")", s.find(MyString("world")), 6);
    printResult("find(\"xyz\")", s.find(MyString("xyz")), MyString::npos);

    // find(MyString) with a starting position
    MyString s2 = "abcabc";
    printResult("find(\"abc\", pos=1)", s2.find(MyString("abc"), 1), 3);

    // find(const char*)
    printResult("find(\"world\" as const char*)", s.find("world"), 6);

    // find(char)
    printResult("find('w')", s.find('w'), 6);
    printResult("find('z')", s.find('z'), MyString::npos);

    // find on empty string
    MyString empty;
    printResult("empty.find('a')", empty.find('a'), MyString::npos);

    return 0;
}