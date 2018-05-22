#ifndef __COLOR_PRINT_H__
#define __COLOR_PRINT_H__

#include <stdlib.h>

//#define CONSOLE_COLOR_RED      FOREGROUND_RED
//#define CONSOLE_COLOR_GREEN    FOREGROUND_GREEN
//#define CONSOLE_COLOR_BLUE     FOREGROUND_BLUE

#define CONSOLE_COLOR_RED    12 
#define CONSOLE_COLOR_GREEN   6
#define CONSOLE_COLOR_BLUE    9
#define CONSOLE_COLOR_YELLOW 14
#define CONSOLE_COLOR_WHITE  15
#define CONSOLE_COLOR_PURPLE 13
#define CONSOLE_COLOR_BLACK   0

#define CONSOLE_SET_COLOR(k)      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  k);
#define CONSOLE_SET_TEXT_RED      CONSOLE_SET_COLOR(CONSOLE_COLOR_RED)
#define CONSOLE_SET_TEXT_GREEN    CONSOLE_SET_COLOR(CONSOLE_COLOR_GREEN)
#define CONSOLE_SET_TEXT_BLUE     CONSOLE_SET_COLOR(CONSOLE_COLOR_BLUE)
#define CONSOLE_SET_TEXT_YELLOW   CONSOLE_SET_COLOR(CONSOLE_COLOR_YELLOW)
#define CONSOLE_SET_TEXT_WHITE    CONSOLE_SET_COLOR(CONSOLE_COLOR_WHITE)
#define CONSOLE_SET_TEXT_PURPLE   CONSOLE_SET_COLOR(CONSOLE_COLOR_PURPLE)



#define CONSOLE_COLOR_PRINT_SHOW_DEMO                                   \
    for (int k = 0; k < 255; k++)                                       \
    {                                                                   \
        CONSOLE_SET_COLOR(k);                                           \
        printf("%3d --> Pick a style you prefer !\r\n", k);             \
    }                                                                   \

#define CONSOLE_SET_STYLE(TEXT_COLOR,BACK_COLOR) CONSOLE_SET_COLOR(BACK_COLOR*16 + TEXT_COLOR);
#define CONSOLE_RESET_DEFAULT                    CONSOLE_SET_STYLE(CONSOLE_COLOR_WHITE,CONSOLE_COLOR_BLACK)
#endif