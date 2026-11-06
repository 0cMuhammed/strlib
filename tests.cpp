#include <iostream>
#include "MyString.h"

const long long NPOS = static_cast<long long>(MyString::npos); // -1

int sgn(int x) { return (x > 0) - (x < 0); }

void printResults(const char* label, long long actual, long long expected, bool isIndex = true)
{
    std::cout << label << " -> ";
    if (isIndex && actual == NPOS) std::cout << "npos";
    else                           std::cout << actual;

    if (actual == expected) std::cout << "  PASS\n";
    else
    {
        std::cout << "  FAIL (expected ";
        if (isIndex && expected == NPOS) std::cout << "npos";
        else                             std::cout << expected;
        std::cout << ")\n";
    }
}

// compare returns a - b on a mismatch, so only the sign is checked
void testCompare()
{
    std::cout << "\n===== compare =====\n";

    MyString abc("abc");

    // compare(const MyString&)
    printResults("abc.compare(MyString(\"abc\"))", sgn(abc.compare(MyString("abc"))), 0, false);
    printResults("abc.compare(MyString(\"abd\"))", sgn(abc.compare(MyString("abd"))), -1, false);
    printResults("abc.compare(MyString(\"abb\"))", sgn(abc.compare(MyString("abb"))), 1, false);
    printResults("abc.compare(MyString(\"abcd\"))", sgn(abc.compare(MyString("abcd"))), -1, false);
    printResults("abc.compare(MyString(\"ab\"))", sgn(abc.compare(MyString("ab"))), 1, false);
    printResults("abc.compare(MyString(\"\"))", sgn(abc.compare(MyString(""))), 1, false);
    printResults("empty.compare(MyString(\"abc\"))", sgn(MyString("").compare(MyString("abc"))), -1, false);
    printResults("empty.compare(MyString(\"\"))", sgn(MyString("").compare(MyString(""))), 0, false);
    printResults("Z.compare(MyString(\"a\"))", sgn(MyString("Z").compare(MyString("a"))), -1, false);
    printResults("a.compare(MyString(\"Z\"))", sgn(MyString("a").compare(MyString("Z"))), 1, false);

    // compare(const char*)
    printResults("abc.compare(\"abc\")", sgn(abc.compare("abc")), 0, false);
    printResults("abc.compare(\"abd\")", sgn(abc.compare("abd")), -1, false);
    printResults("abc.compare(\"abb\")", sgn(abc.compare("abb")), 1, false);
    printResults("abc.compare(\"abcd\")", sgn(abc.compare("abcd")), -1, false);
    printResults("abc.compare(\"ab\")", sgn(abc.compare("ab")), 1, false);
    printResults("abc.compare(\"\")", sgn(abc.compare("")), 1, false);
    printResults("empty.compare(\"abc\")", sgn(MyString("").compare("abc")), -1, false);
    printResults("empty.compare(\"\")", sgn(MyString("").compare("")), 0, false);
    printResults("abc.compare(nullptr)", sgn(abc.compare(static_cast<const char*>(nullptr))), 1, false);
    printResults("empty.compare(nullptr)", sgn(MyString("").compare(static_cast<const char*>(nullptr))), 0, false);
}

void testFindFirstOf()
{
    std::cout << "\n===== find_first_of =====\n";

    MyString hw("hello world");
    MyString abc("ABCXYZ");
    MyString empty("");

    // const char*
    printResults("hw.find_first_of(\"aeiou\")", hw.find_first_of("aeiou"), 1);
    printResults("hw.find_first_of(\"aeiou\", 2)", hw.find_first_of("aeiou", 2), 4);
    printResults("hw.find_first_of(\"aeiou\", 5)", hw.find_first_of("aeiou", 5), 7);
    printResults("hw.find_first_of(\"aeiou\", 8)", hw.find_first_of("aeiou", 8), NPOS);
    printResults("hw.find_first_of(\"aeiou\", 100)", hw.find_first_of("aeiou", 100), NPOS);
    printResults("hw.find_first_of(\"xyz\")", hw.find_first_of("xyz"), NPOS);
    printResults("hw.find_first_of(\"ol\")", hw.find_first_of("ol"), 2);
    printResults("hw.find_first_of(\"d\")", hw.find_first_of("d"), 10);
    printResults("hw.find_first_of(\"\")", hw.find_first_of(""), NPOS);
    printResults("empty.find_first_of(\"abc\")", empty.find_first_of("abc"), NPOS);
    printResults("abc.find_first_of(\"ZYX\")", abc.find_first_of("ZYX"), 3);

    // const MyString&
    printResults("hw.find_first_of(MyString(\"aeiou\"))", hw.find_first_of(MyString("aeiou")), 1);
    printResults("hw.find_first_of(MyString(\"aeiou\"), 5)", hw.find_first_of(MyString("aeiou"), 5), 7);
    printResults("hw.find_first_of(MyString(\"xyz\"))", hw.find_first_of(MyString("xyz")), NPOS);
    printResults("hw.find_first_of(MyString(\"\"))", hw.find_first_of(MyString("")), NPOS);
    printResults("empty.find_first_of(MyString(\"abc\"))", empty.find_first_of(MyString("abc")), NPOS);
    printResults("abc.find_first_of(MyString(\"ZYX\"))", abc.find_first_of(MyString("ZYX")), 3);

    // const char*, pos, n
    printResults("hw.find_first_of(\"aeiou\", 0, 5)", hw.find_first_of("aeiou", 0, 5), 1);
    printResults("hw.find_first_of(\"aeiou\", 0, 1)", hw.find_first_of("aeiou", 0, 1), NPOS);
    printResults("hw.find_first_of(\"oel\", 0, 2)", hw.find_first_of("oel", 0, 2), 1);
    printResults("hw.find_first_of(\"oel\", 2, 2)", hw.find_first_of("oel", 2, 2), 4);
    printResults("hw.find_first_of(\"old\", 0, 3)", hw.find_first_of("old", 0, 3), 2);
    printResults("hw.find_first_of(\"old\", 0, 1)", hw.find_first_of("old", 0, 1), 4);
    printResults("hw.find_first_of(\"aeiou\", 0, 0)", hw.find_first_of("aeiou", 0, 0), NPOS);
    printResults("hw.find_first_of(\"aeiou\", 100, 5)", hw.find_first_of("aeiou", 100, 5), NPOS);
    printResults("empty.find_first_of(\"abc\", 0, 3)", empty.find_first_of("abc", 0, 3), NPOS);

    // char
    printResults("hw.find_first_of('o')", hw.find_first_of('o'), 4);
    printResults("hw.find_first_of('o', 5)", hw.find_first_of('o', 5), 7);
    printResults("hw.find_first_of('z')", hw.find_first_of('z'), NPOS);
    printResults("empty.find_first_of('a')", empty.find_first_of('a'), NPOS);
}

void testFindLastOf()
{
    std::cout << "\n===== find_last_of =====\n";

    MyString hw("hello world");
    MyString abc("ABCXYZ");
    MyString empty("");

    // const char*
    printResults("hw.find_last_of(\"aeiou\")", hw.find_last_of("aeiou"), 7);
    printResults("hw.find_last_of(\"aeiou\", 5)", hw.find_last_of("aeiou", 5), 4);
    printResults("hw.find_last_of(\"aeiou\", 7)", hw.find_last_of("aeiou", 7), 7);
    printResults("hw.find_last_of(\"aeiou\", 6)", hw.find_last_of("aeiou", 6), 4);
    printResults("hw.find_last_of(\"aeiou\", 100)", hw.find_last_of("aeiou", 100), 7);
    printResults("hw.find_last_of(\"h\", 0)", hw.find_last_of("h", 0), 0);
    printResults("hw.find_last_of(\"e\", 0)", hw.find_last_of("e", 0), NPOS);
    printResults("hw.find_last_of(\"xyz\")", hw.find_last_of("xyz"), NPOS);
    printResults("hw.find_last_of(\"ol\")", hw.find_last_of("ol"), 9);
    printResults("hw.find_last_of(\"\")", hw.find_last_of(""), NPOS);
    printResults("abc.find_last_of(\"XA\")", abc.find_last_of("XA"), 3);
    printResults("empty.find_last_of(\"abc\")", empty.find_last_of("abc"), NPOS);

    // const MyString&
    printResults("hw.find_last_of(MyString(\"aeiou\"))", hw.find_last_of(MyString("aeiou")), 7);
    printResults("hw.find_last_of(MyString(\"aeiou\"), 5)", hw.find_last_of(MyString("aeiou"), 5), 4);
    printResults("hw.find_last_of(MyString(\"aeiou\"), 7)", hw.find_last_of(MyString("aeiou"), 7), 7);
    printResults("hw.find_last_of(MyString(\"aeiou\"), 100)", hw.find_last_of(MyString("aeiou"), 100), 7);
    printResults("hw.find_last_of(MyString(\"xyz\"))", hw.find_last_of(MyString("xyz")), NPOS);
    printResults("hw.find_last_of(MyString(\"ol\"))", hw.find_last_of(MyString("ol")), 9);
    printResults("hw.find_last_of(MyString(\"\"))", hw.find_last_of( MyString("")), NPOS);
    printResults("abc.find_last_of(MyString(\"XA\"))", abc.find_last_of(MyString("XA")), 3);
    printResults("empty.find_last_of(MyString(\"abc\"))", empty.find_last_of(MyString("abc")), NPOS);

    // const char*, pos, n
    printResults("hw.find_last_of(\"aeiou\", npos, 5)", hw.find_last_of("aeiou", MyString::npos, 5), 7);
    printResults("hw.find_last_of(\"aeiou\", npos, 2)", hw.find_last_of("aeiou", MyString::npos, 2), 1);
    printResults("hw.find_last_of(\"aeiou\", npos, 1)", hw.find_last_of("aeiou", MyString::npos, 1), NPOS);
    printResults("hw.find_last_of(\"old\", npos, 1)", hw.find_last_of("old", MyString::npos, 1), 7);
    printResults("hw.find_last_of(\"old\", npos, 2)", hw.find_last_of("old", MyString::npos, 2), 9);
    printResults("hw.find_last_of(\"old\", npos, 3)", hw.find_last_of("old", MyString::npos, 3), 10);
    printResults("hw.find_last_of(\"aeiou\", npos, 0)", hw.find_last_of("aeiou", MyString::npos, 0), NPOS);
    printResults("hw.find_last_of(\"xyz\", npos, 3)", hw.find_last_of("xyz", MyString::npos, 3), NPOS);
    printResults("hw.find_last_of(\"aeiou\", 5, 5)", hw.find_last_of("aeiou", 5, 5), 4);
    printResults("hw.find_last_of(\"aeiou\", 7, 5)", hw.find_last_of("aeiou", 7, 5), 7);
    printResults("hw.find_last_of(\"aeiou\", 6, 5)", hw.find_last_of("aeiou", 6, 5), 4);
    printResults("hw.find_last_of(\"h\", 0, 1)", hw.find_last_of("h", 0, 1), 0);
    printResults("hw.find_last_of(\"e\", 0, 1)", hw.find_last_of("e", 0, 1), NPOS);
    printResults("hw.find_last_of(\"aeiou\", 100, 5)", hw.find_last_of("aeiou", 100, 5), 7);
    printResults("abc.find_last_of(\"XA\", npos, 2)", abc.find_last_of("XA", MyString::npos, 2), 3);
    printResults("abc.find_last_of(\"XA\", npos, 1)", abc.find_last_of("XA", MyString::npos, 1), 3);
    printResults("abc.find_last_of(\"AX\", npos, 1)", abc.find_last_of("AX", MyString::npos, 1), 0);
    printResults("empty.find_last_of(\"abc\", npos, 3)", empty.find_last_of("abc", MyString::npos, 3), NPOS);

    const char buf[] = { 'x', 'y', 'l' }; // no '\0': n defines the bag
    printResults("hw.find_last_of(buf, npos, 2)", hw.find_last_of(buf, MyString::npos, 2), NPOS);
    printResults("hw.find_last_of(buf, npos, 3)", hw.find_last_of(buf, MyString::npos, 3), 9);

    // char
    printResults("hw.find_last_of('o')", hw.find_last_of('o'), 7);
    printResults("hw.find_last_of('o', 5)", hw.find_last_of('o', 5), 4);
    printResults("hw.find_last_of('o', 7)", hw.find_last_of('o', 7), 7);
    printResults("hw.find_last_of('z')", hw.find_last_of('z'), NPOS);
    printResults("empty.find_last_of('a')", empty.find_last_of('a'), NPOS);
}

int main()
{
    testCompare();
    testFindFirstOf();
    testFindLastOf();
    return 0;
}