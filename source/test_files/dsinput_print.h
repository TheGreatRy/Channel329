#include <nds.h>
#include <stdio.h>
#include <string>

class PrintDSInput
{
    public:
    PrintDSInput() = default;
    ~PrintDSInput() = default;

    void printInput(KEYPAD_BITS inputKey);

};