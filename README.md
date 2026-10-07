# moloney_enum
An efficient c++ enum reflection library

## How to use:
Just declare an enum using the DECLARE_ENUM macro (demonstrated below) and you will then be able to run your enum through get_enum_as_string() to get the reflected string.
```cpp
#include <iostream>
#include "moloney_enum.h" // or whatever path it may be


DECLARE_ENUM(/*Enum Name:*/ TestEnum, /*Values:*/I, Am, The, Enum, Man);

int main() {
    TestEnum test_value = Man;
    std::cout << get_enum_as_string<TestEnum>(test_value) << "\n";
}
```

## TO BE ADDED:
String to enum conversion.
Nicer (and more efficient) constexpr code for generating the enum's string views.
Enum class support with inheritance.
Support for enums with explicitly defined values (and negative values). For example: `Value1 = -1, Value2 = 5`.