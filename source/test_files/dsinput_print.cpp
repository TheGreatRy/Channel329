#include "dsinput_print.h"

void PrintDSInput::printInput(KEYPAD_BITS inputKey)
{
     switch (inputKey)
     {
        case KEY_A:
             printf("A Button");
             break;
        case KEY_B:
             printf("B Button");
             break;
        case KEY_X:
            printf("X Button");
            break;
        case KEY_Y:
            printf("Y Button");
            break;
        case KEY_UP:
            printf("DPAD UP");
            break;
        case KEY_DOWN:
            printf("DPAD Down");
            break;
        case KEY_LEFT:
            printf("DPAD Left");
            break;
        case KEY_RIGHT:
            printf("DPAD Right");
            break;
        case KEY_START:
            printf("Start Button");
            break;
        case KEY_SELECT:
            printf("Select Button");
            break;
        case KEY_L:
            printf("Left Bumper");
            break;
        case KEY_R:
            printf("Right Bumper");
            break;
        default:
            printf("Other Input");
            break;
     }
}
