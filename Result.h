#ifndef RESULT_H
#define RESULT_H




typedef enum{
    RESULT_OK,
    RESULT_FULL,
    RESULT_EMPTY,
    RESULT_DUPLICATE,
    RESULT_USORTED
} Result;



void print_result(Result);
void print_menu(void);


#endif