#ifndef STACK_H
#define STACK_H

#include "basic_types.h"
#include <stdio.h>
#include <stdlib.h>
#include "generic_collection_types.h"

#define MAXSTACK 2024
typedef struct _Stack Stack;

Stack * stack_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4);

void stack_destroy(Stack *);

Stack * stack_push(Stack *, const void *);

void * stack_pop(Stack *);

void * stack_top(const Stack *);

Bool stack_isEmpty(const Stack *);

Bool stack_isFull(const Stack *);

int stack_print(FILE*, const Stack*);

int stack_size(const Stack* );

int stack_compare(const Stack* , const Stack*);

Stack * stack_copy(Stack *);


#endif
