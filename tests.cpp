#include "MyString.h"
#include <iostream>

void printResult(const char* testName, const MyString& result, const char* expected) {
    bool pass = (result == MyString(expected));
    std::cout << (pass ? "[PASS] " : "[FAIL] ") << testName
        << " -> got: \"" << result << "\", expected: \"" << expected << "\"\n";
}

int main() {

    // ---- insert(pos, const MyString&) ----
    MyString s1("Hello");
    MyString obj1("xyz");
    s1.insert(2, obj1);
    printResult("insert(pos, MyString)", s1, "Hexyzllo");

    MyString s2("Hello");
    MyString obj2("xyz");
    s2.insert(5, obj2); // pos == length
    printResult("insert(pos==length, MyString)", s2, "Helloxyz");

    MyString s3("Hello");
    MyString obj3("xyz");
    try {
        s3.insert(100, obj3);
        std::cout << "[FAIL] insert(MyString) out_of_range not thrown\n";
    }
    catch (const std::out_of_range&) {
        std::cout << "[PASS] insert(MyString) out_of_range thrown correctly\n";
    }

    // ---- insert(pos, const char*) ----
    MyString s4("Hello");
    s4.insert(2, "xyz");
    printResult("insert(pos, const char*)", s4, "Hexyzllo");

    MyString s5("Hello");
    s5.insert(5, "xyz"); // pos == length
    printResult("insert(pos==length, const char*)", s5, "Helloxyz");

    MyString s6("Hello");
    try {
        s6.insert(2, static_cast<const char*>(nullptr));
        std::cout << "[FAIL] insert(const char*) nullptr not thrown\n";
    }
    catch (const std::invalid_argument&) {
        std::cout << "[PASS] insert(const char*) nullptr thrown correctly\n";
    }

    // ---- insert(pos, size_t copies, char c) ----
    MyString s7("Hello");
    s7.insert(2, 3, 'x');
    printResult("insert(pos, n, char)", s7, "Hexxxllo");

    MyString s8("Hello");
    s8.insert(5, 3, 'x'); // pos == length
    printResult("insert(pos==length, n, char)", s8, "Helloxxx");

    MyString s9("Hello");
    s9.insert(2, 0, 'x'); // zero copies -> no change
    printResult("insert(pos, 0, char)", s9, "Hello");

    // ---- insert(pos, const char* str, size_t endLimit) ----
    MyString s10("Hello");
    s10.insert(2, "xyzabc", 3); // only "xyz"
    printResult("insert(pos, str, n)", s10, "Hexyzllo");

    MyString s11("Hello");
    s11.insert(5, "xyzabc", 3); // pos == length, only first 3 chars
    printResult("insert(pos==length, str, n)", s11, "Helloxyz");

    MyString s12("Hello");
    try {
        s12.insert(2, static_cast<const char*>(nullptr), 3);
        std::cout << "[FAIL] insert(str,n) nullptr not thrown\n";
    }
    catch (const std::invalid_argument&) {
        std::cout << "[PASS] insert(str,n) nullptr thrown correctly\n";
    }

    // ---- insert(pos, const MyString& obj, subpos, sublen) ----
    MyString s13("Hello");
    MyString obj13("xyzabc");
    s13.insert(2, obj13, 0, 3); // substr(0,3) of "xyzabc" = "xyz"
    printResult("insert(pos, obj, subpos, sublen)", s13, "Hexyzllo");

    MyString s14("Hello");
    MyString obj14("xyz");
    s14.insert(5, obj14, 0, 3); // pos == length
    printResult("insert(pos==length, obj, subpos, sublen)", s14, "Helloxyz");

    MyString s15("Hello");
    MyString obj15("xyz");
    s15.insert(2, obj15, 1, 100); // sublen overshoots -> clamps to "yz"
    printResult("insert(pos, obj, subpos, sublen overshoot)", s15, "Heyzllo");

    // ==================== substr(pos) ====================
    MyString sub1("Hello");
    MyString r1 = sub1.substr(0);
    printResult("substr(pos=0)", r1, "Hello");

    MyString sub2("Hello");
    MyString r2 = sub2.substr(2);
    printResult("substr(pos=2)", r2, "llo");

    MyString sub3("Hello");
    MyString r3 = sub3.substr(5); // pos == length -> empty string
    printResult("substr(pos==length)", r3, "");

    MyString sub4("Hello");
    try {
        MyString r4 = sub4.substr(100);
        std::cout << "[FAIL] substr(pos) out_of_range not thrown\n";
    }
    catch (const std::out_of_range&) {
        std::cout << "[PASS] substr(pos) out_of_range thrown correctly\n";
    }

    // ==================== substr(pos, length) ====================
    MyString sub5("Hello");
    MyString r5 = sub5.substr(1, 3);
    printResult("substr(pos, length)", r5, "ell");

    MyString sub6("Hello");
    MyString r6 = sub6.substr(0, 5); // full length
    printResult("substr(pos=0, full length)", r6, "Hello");

    MyString sub7("Hello");
    MyString r7 = sub7.substr(2, 0); // zero length -> empty string
    printResult("substr(pos, length=0)", r7, "");

    MyString sub8("Hello");
    MyString r8 = sub8.substr(2, 100); // length overshoots -> clamps to rest of string
    printResult("substr(pos, length overshoot)", r8, "llo");

    MyString sub9("Hello");
    try {
        MyString r9 = sub9.substr(100, 2);
        std::cout << "[FAIL] substr(pos, length) out_of_range not thrown\n";
    }
    catch (const std::out_of_range&) {
        std::cout << "[PASS] substr(pos, length) out_of_range thrown correctly\n";
    }
    std::cout << "\nAll tests executed.\n";
    return 0;
}