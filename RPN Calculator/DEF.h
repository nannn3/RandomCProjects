//Making some standard definitons I'm using

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef STANDARD_ERROR_ENUM
typedef enum {
    SIZE_ERROR = -1,
    STANDARD_ERROR,
    SUCCESS
} STANDARD_ERROR_ENUM;
#endif

#ifndef BOOL
typedef enum _BOOL { FALSE = 0, TRUE } BOOL;
#endif