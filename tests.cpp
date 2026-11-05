#include "MyString.h"
#include <iostream>



int main() {
   
  
    std::cout << MyString("ABCXYZ").find_first_of("ZYX") << std::endl;
  std::cout << MyString("ABCXYZ").find("ZYX");
    return 0;
}