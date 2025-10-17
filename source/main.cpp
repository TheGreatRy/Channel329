// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2025 

#include <nds.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include <filesystem.h>
#include <fat.h>



typedef void (fnptrvoid)(void);
typedef int (fnptr1int)(int);
typedef int (fnptr2int)(int, int);


int main(int argc, char **argv)
{
    //Set up exception handler
    defaultExceptionHandler();

    

    return 0;
}
