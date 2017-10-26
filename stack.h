#ifndef STACK_H
#define STACK_H

#include "basic_types.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSTACK 2024
typedef struct _Stack Stack;

typedef void (*destroy_element_function_type)(void*);
typedef void (*(*copy_element_function_type)(const void*));
typedef int (*print_element_function_type)(FILE *, const void*);

Stack * stack_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type​ ​f4​);

void stack_destroy(Stack *);

Stack * stack_push(Stack *, const void *);

void * stack_pop(Stack *);

void * stack_top(const Stack *);

Bool stack_isEmpty(const Stack *);

Bool stack_isFull(const Stack *);

int stack_print(FILE*, const Stack*);

int stack_size(const Stack* );

int stack_compare(const s1*, const s2*);


#endif
