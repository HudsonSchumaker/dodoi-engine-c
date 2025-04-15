/**
* @file stack.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_collection.h"

#define STACK_INIT_CAPACITY 64
#define STACK_RESIZE_FACTOR 128

void stack_init(stack_t* stack, size_t type_size) {
    stack->size = 0;
    stack->capacity = STACK_INIT_CAPACITY;
    stack->type_size = type_size;
    stack->array = malloc(stack->capacity * stack->type_size);
    if (!stack->array) {
        fprintf(stderr, "ERROR: stack_t, memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

void stack_push(stack_t* stack, void* value) {
    if (stack->size == stack->capacity) {
        stack->capacity += STACK_RESIZE_FACTOR;
        void* new_array = realloc(stack->array, stack->capacity * stack->type_size);
        if (new_array) {
            stack->array = new_array;
        }
        else {
            fprintf(stderr, "ERROR: stack_t, memory reallocation failed\n");
            return;
        }
    }
    memcpy((char*)stack->array + stack->size * stack->type_size, value, stack->type_size);
    stack->size++;
}

void* stack_pop(stack_t* stack) {
    if (stack_is_empty(stack)) {
        return NULL;
    }
    stack->size--;
    return (char*)stack->array + stack->size * stack->type_size;
}

bool stack_is_empty(stack_t* stack) {
    return stack->size == 0;
}

void stack_free(stack_t* stack) {
    free(stack->array);
    stack->array = NULL;
    stack->size = 0;
    stack->capacity = 0;
}
