#ifndef STACK_H
#define STACK_H

#include <string.h>
#include "Result.h"
#include <stdbool.h>
#include <stdio.h>
#define CAPACITY 100

typedef struct 
{
    char key[101];
    int value;
} Element;



typedef struct 
{
    Element items[CAPACITY];
    size_t size;
   
} Stack;


void stack_init(Stack*);
bool stack_is_empty(const Stack*);
size_t stack_count(const Stack*);
int stack_find(const Stack*, const char*);
Result stack_push(Stack*, Element);
Result stack_pop(Stack*, Element*);
void stack_sort(Stack*);
bool stack_is_sorted(const Stack*);
Result stack_insert_sorted(Stack*, Element);
void print_element(const Element*);
Result print_stack(const Stack*);
void stack_print_internal(const Stack*);


#endif


