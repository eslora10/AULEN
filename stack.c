#include "stack.h"

struct _Stack {
    int top;
    void **items;
    destroy_element_function_type destroy_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
};

Stack * stack_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3) {
    Stack *s = NULL;

    s = (Stack*) malloc(sizeof (Stack));

    if (!s)
        return NULL;

    s->top = -1;
    s->items = NULL;
    s->destroy_element_function = f1;
    s->copy_element_function = f2;
    s->print_element_function = f3;

    return s;
}

void stack_destroy(Stack *s) {
    int i;

    if (!s) return;

    for (i = s->top; i >= 0; i--) {
        s->destroy_element_function(s->items[i]);
    }
    free(s->items);
    free(s);

    return;
}

Stack * stack_push(Stack *s, const void *item) {

    if (!s || s->top == MAXSTACK - 1)
        return NULL;

    s->top++;
    s->items = realloc(s->items, (s->top + 1) * sizeof (s->items[0]));

    if (!s->items)
        return NULL;

    s->items[s->top] = s->copy_element_function(item);

    return s;
}

void * stack_pop(Stack *s) {
    void *item;

    if (!s || s->top < 0)
        return NULL;

    item = s->items[s->top];

    if (s->top != 0) s->items = realloc(s->items, (s->top) * sizeof (s->items[0]));

    if (!s->items)
        return NULL;

    s->top--;

    return item;
}

void * stack_top(const Stack *s) {
    if (!s)
        return NULL;

    return s->copy_element_function(s->items[s->top]);
}

Bool stack_isEmpty(const Stack *s) {
    if (!s)
        return FALSE;

    if (s->top > -1)
        return FALSE;
    return TRUE;

}

Bool stack_isFull(const Stack * s) {
    if (!s)
        return FALSE;
    return s->top == MAXSTACK - 1;
}

int stack_print(FILE* fp, const Stack* s) {
    int i, nchar = 0;

    if (!fp || !s)
        return -1;

    for (i = s->top; i >= 0; i--) {
        nchar += s->print_element_function(fp, s->items[i]);
    }

    return nchar;

}

int stack_size(const Stack* s) {
    return s->top + 1;
}

Stack * stack_copy(Stack * s){
    Stack* new = NULL;
    int i;
    
    if(!s) return NULL;
    
    new = stack_ini(s->destroy_element_function, s->copy_element_function, 
    s->print_element_function);
    
    if(!new) return NULL;
    
    for (i = 0; i <= s->top; i++){
        stack_push(new, s->items[i]);
    }
    
    
    return new;
}
