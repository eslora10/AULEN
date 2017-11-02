#include "stack.h"
#include <string.h>

void destroy_p_string(void* s){
    free(s);    
}

void *copy_p_string(const void* s1){
    char *s2;
    
    s2 = (char*)malloc(sizeof(char)* strlen((char*)s1)+1);
    
    strcpy(s2, (char*)s1);
    
    return s2;
    
}
int print_p_string(FILE *f, const void*s){
    return fprintf(f, "%s\n", (char*)s);
}

int main(int argc, char** argv)
{
    Stack * p_s_string1, * p_s_string2;
    char * aux_string;

    p_s_string1 = (Stack *) stack_ini(    destroy_p_string, copy_p_string, print_p_string, (cmp_element_function_type) strcmp);
    p_s_string2 = (Stack *) stack_ini(    destroy_p_string, copy_p_string, print_p_string, (cmp_element_function_type) strcmp);



    
    stack_push(p_s_string1, "hola 1");
    stack_push(p_s_string1, "hola 2");
    stack_push(p_s_string1, "hola 3");
    stack_push(p_s_string1, "hola 4");
    stack_push(p_s_string1, "hola 5");
    stack_push(p_s_string1, "hola 6");
    stack_push(p_s_string1, "hola 7");

    while(!stack_isEmpty(p_s_string1))
    {              
        aux_string = stack_pop(p_s_string1);
        stack_push(p_s_string2, aux_string);
        destroy_p_string(aux_string);

    }
    
    stack_print(stdout,p_s_string2);

    stack_destroy(p_s_string2);
    stack_destroy(p_s_string1);

    return 0;

}


