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
   
    const size_t npos = MyString::npos;

    MyString abc9("abcabcabc");
    MyString hello("hello");
    MyString empty("");
    MyString abc("abc");
    MyString aaaa("aaaa");
    MyString abcabc("abcabc");

    // ---- const char* overload ----
    printResult("1  abcabcabc rfind(\"abc\")", abc9.rfind("abc"), 6);
    printResult("2  abcabcabc rfind(\"abc\", 5)", abc9.rfind("abc", 5), 3);
    printResult("3  abcabcabc rfind(\"abc\", 3)", abc9.rfind("abc", 3), 3);
    printResult("4  abcabcabc rfind(\"abc\", 2)", abc9.rfind("abc", 2), 0);
    printResult("5  abcabcabc rfind(\"xyz\")", abc9.rfind("xyz"), npos);

    // ---- char overload ----
    printResult("6  hello rfind('l')", hello.rfind('l'), 3);
    printResult("7  hello rfind('l', 2)", hello.rfind('l', 2), 2);
    printResult("8  hello rfind('h', 0)", hello.rfind('h', 0), 0);
    printResult("9  hello rfind('z')", hello.rfind('z'), npos);

    // ---- empty pattern ----
    printResult("10 hello rfind(\"\")", hello.rfind(""), 5);
    printResult("11 hello rfind(\"\", 2)", hello.rfind("", 2), 2);

    // ---- empty string ----
    printResult("12 \"\" rfind('a')", empty.rfind('a'), npos);
    printResult("13 \"\" rfind(\"\")", empty.rfind(""), 0);

    // ---- pattern longer than string ----
    printResult("14 abc rfind(\"abcd\")", abc.rfind("abcd"), npos);

    // ---- overlapping ----
    printResult("15 aaaa rfind(\"aa\")", aaaa.rfind("aa"), 2);

    // ---- 3-argument overload ----
    printResult("16 abcabc rfind(\"abcXYZ\", npos, 3)", abcabc.rfind("abcXYZ", npos, 3), 3);

    // ---- pos larger than length ----
    printResult("17 abc rfind(\"c\", 1000)", abc.rfind("c", 1000), 2);

    // ---- MyString overload ----
    printResult("18 abc rfind(MyString(\"bc\"))", abc.rfind(MyString("bc")), 1);
    printResult("19 abc rfind(MyString(\"a\"), 0)", abc.rfind(MyString("a"), 0), 0);
    printResult("20 abc rfind(MyString(\"b\"), 0)", abc.rfind(MyString("b"), 0), npos);

    // ---- extra edge cases ----
    printResult("21 xabc rfind(\"abc\") (start index, not length)", MyString("xabc").rfind("abc"), 1);
    printResult("22 abc rfind(MyString(\"\"))", abc.rfind(MyString("")), 3);
    printResult("23 \"\" rfind(MyString(\"\"))", empty.rfind(MyString("")), 0);
    printResult("24 abc rfind(\"abc\", 0, 0) (n = 0 means empty pattern)", abc.rfind("abc", npos, 0), 3);
    printResult("25 abc rfind(\"abc\", npos, 10) (n clamped)", abc.rfind("abc", npos, 10), 0);
    printResult("26 a rfind('a')", MyString("a").rfind('a'), 0);
    printResult("27 abc rfind(\"abc\")", abc.rfind("abc"), 0);


    return 0;
}