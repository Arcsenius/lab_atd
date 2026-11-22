#include "Stack.h"



void stack_init(Stack* stack){
    stack->size = 0;
}


bool stack_is_empty(const Stack* stack){
    return stack->size == 0;
}


size_t stack_count(const Stack* stack){
    return stack->size;
}


int stack_find(const Stack* stack, const char* key){
    size_t i = 0;
    for(; i < stack->size; ++i){
        if(strcmp(stack->items[i].key, key) == 0){ // strcmp string compare - сравнение строк
            return (int)i;
        }
    }
    return -1;
}


Result stack_push(Stack* stack, Element element){
    if (stack->size == CAPACITY){
        return RESULT_FULL;
    }
    if (stack_find(stack, element.key) != -1){
        return RESULT_DUPLICATE;
    }

    stack->items[stack->size++] = element;
    return RESULT_OK;
}

Result stack_pop(Stack* stack, Element* removed){
    if (stack_is_empty(stack)){
        return RESULT_EMPTY;
    }
    *removed = stack->items[--stack->size];
    return RESULT_OK;
}

/* Сортировка по ключу (строке) */
void stack_sort(Stack* stack){
    size_t end = stack->size;
    for (; end > 1; --end){
        int flag = 0;
        size_t i = 0;
        for (; i + 1 < end; ++i){
            if (strcmp(stack->items[i].key, stack->items[i + 1].key) > 0){
                Element temp = stack->items[i];
                stack->items[i] = stack->items[i + 1];
                stack->items[i + 1] = temp;
                flag = 1;
            }
        }
        if (!flag) {
            break;
        }
    }
}


bool stack_is_sorted(const Stack* stack){
    size_t i = 1;
    for (; i < stack->size;++i){
        if (strcmp(stack->items[i - 1].key, stack->items[i].key) > 0){
            return false;
        }
    }
    return true;
}



Result stack_insert_sorted(Stack* stack, Element element){
    if (stack->size == CAPACITY){
        return RESULT_FULL;
    }
    if (stack_find(stack, element.key) != -1){
        return RESULT_DUPLICATE;
    }
    if (!stack_is_sorted(stack)){
        return RESULT_USORTED;
    }


    size_t position = stack->size;

    while (position > 0 && strcmp(stack->items[position - 1].key, element.key) > 0){
        stack->items[position] = stack->items[position - 1];
        --position;
    }
    stack->items[position] = element;
    ++stack->size;
    return RESULT_OK;
}


void print_element(const Element* element){
    printf("key=%s, value=%d\n", element->key, element->value);
}


Result print_stack(const Stack* stack){
    if (stack_is_empty(stack)){
        return RESULT_EMPTY;
    }
    puts("Elements from top to bottom\n");
    size_t i = stack->size;
    for (; i > 0 ; --i){
        print_element(&stack->items[i - 1]);
    }
    return RESULT_OK;
}

/* Показываем устройство массива, не читая незанятые ячейки. */
void stack_print_internal(const Stack* stack){
    printf("Stack: size=%zu, capacity=%d\n", stack->size, CAPACITY);
    if (stack_is_empty(stack)){
        puts("top: none");
    } else {
        printf("top: items[%zu]\n", stack->size - 1);
    }
    for (size_t i = 0; i < stack->size; ++i){
        printf("items[%zu]%s: ", i,
               i == stack->size - 1 ? " <- top" : "");
        print_element(&stack->items[i]);
    }
    if (stack->size < CAPACITY){
        printf("items[%zu..%d]: unused\n", stack->size, CAPACITY - 1);
    }
}



