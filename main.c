#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "Result.h"
#include "Stack.h"

#define LINE_CAPACITY 512

/* Проверяем весь токен и переполнение, в отличие от atoi. */
static bool parse_int(const char* text, int* value){
    if (text == NULL || *text == '\0'){
        return false;
    }
    char* end;
    errno = 0;
    long parsed = strtol(text, &end, 10);
    if (errno == ERANGE || *end != '\0' || parsed < INT_MIN || parsed > INT_MAX){
        return false;
    }
    *value = (int)parsed;
    return true;
}

int main(void){
    Stack stack;
    stack_init(&stack);
    puts("Created empty stack");
    print_menu();

    char line[LINE_CAPACITY];
    while (true){
        printf("> ");
        fflush(stdout);
        if (fgets(line, sizeof(line), stdin) == NULL){
            if (ferror(stdin)){
                perror("Input error");
                return EXIT_FAILURE;
            }
            break;
        }

        /* Отбрасываем длинную строку целиком, включая оставшийся хвост. */
        if (strchr(line, '\n') == NULL){
            int ch = getchar();
            if (ch != '\n' && ch != EOF){
                while ((ch = getchar()) != '\n' && ch != EOF){}
                puts("Error: input line is too long");
                continue;
            }
        }

        char* command_text = strtok(line, " \t\r\n");
        if (command_text == NULL){
            continue;
        }
        char* key = strtok(NULL, " \t\r\n");
        char* value_text = strtok(NULL, " \t\r\n");
        char* extra = strtok(NULL, " \t\r\n");
        int command;
        if (!parse_int(command_text, &command) || command < 0 || command > 10){
            puts("Error: command must be a number from 0 to 10");
            continue;
        }

        Element element;
        if (command == 2 || command == 9){
            if (key == NULL || strlen(key) >= sizeof(element.key) ||
                !parse_int(value_text, &element.value) || extra != NULL){
                puts("Error: expected <command> <key of 1-100 bytes> <int>");
                continue;
            }
            strcpy(element.key, key);
        } else if (command == 10){
            if (key == NULL || strlen(key) >= sizeof(element.key) || value_text != NULL){
                puts("Error: expected 10 <key of 1-100 bytes>");
                continue;
            }
        } else if (key != NULL){
            puts("Error: this command takes no arguments");
            continue;
        }

        switch (command){
            case 0:
                return EXIT_SUCCESS;
            case 1:
                stack_init(&stack);
                puts("Created empty stack");
                break;
            case 2:
                print_result(stack_push(&stack, element));
                break;
            case 3: {
                Result result = stack_pop(&stack, &element);
                if (result == RESULT_OK){
                    printf("Removed: ");
                    print_element(&element);
                } else {
                    print_result(result);
                }
                break;
            }
            case 4:
                puts(stack_is_empty(&stack) ? "Stack is empty" : "Stack is not empty");
                break;
            case 5:
                printf("Element count: %zu\n", stack_count(&stack));
                break;
            case 6:
                stack_sort(&stack);
                puts("Stack sorted by key (ascending array indices)");
                break;
            case 7: {
                Result result = print_stack(&stack);
                if (result != RESULT_OK){
                    print_result(result);
                }
                break;
            }
            case 8:
                stack_print_internal(&stack);
                break;
            case 9:
                print_result(stack_insert_sorted(&stack, element));
                break;
            case 10: {
                int index = stack_find(&stack, key);
                if (index < 0){
                    puts("Key not found");
                } else {
                    print_element(&stack.items[index]);
                }
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}
