#include <iostream>
#include "moloney_enum.h" // or whatever path it may be

DECLARE_ENUM(/*Enum Name:*/ TestEnum, /*Values:*/ I, Am, The, Enum, Man);

int main()
{
    TestEnum test_value = Man;
    std::cout << get_enum_as_string<TestEnum>(test_value) << "\n";
}