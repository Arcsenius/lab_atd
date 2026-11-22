#include "Result.h"
#include <stdio.h>



void print_result(Result result){
    switch (result){
        case RESULT_OK:
            puts("Operation completed");
            break;
        case RESULT_FULL:
            puts("Error: stack is full\n");
            break;
        case RESULT_EMPTY:
            puts("Error: stack is empty\n");
            break;
        case RESULT_DUPLICATE:
            puts("Error: Same key exists already\n");
            break;
        case RESULT_USORTED:
            puts("Error: stack is unsorted\n");
            break;
    }
}



void print_menu(void){
    puts("\n Stack: string key, int value\n");
    puts("1. Create empty stack\n");
    puts("2. Add element top (push)\n");
    puts("3. Delete top element (pop)\n");
    puts("4. Check if the stack is empty\n");
    puts("5. Count elements");
    puts("6. Sort stack\n");
    puts("7. Print all elements\n");
    puts("8. Print internal view\n");
    puts("9. Add an element while preserving the order\n");
    puts("10. Find value with help key\n");
    puts("0. Exit");
    puts("Enter one command per line: <number> [key] [value]");
    puts("2 <key> <int> | 9 <key> <int> | 10 <key>");
    puts("Keys: 1-100 bytes, without spaces. Other commands take no arguments.");
}
