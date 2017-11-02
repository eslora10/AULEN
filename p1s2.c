#include <string.h>
#include <stdio.h>
#include "configuracion_ap.h"
#include "estado.h"
#include "stack.h"
#include "palabra.h"
#include "dynamic_node.h"
#include "configuracion_apnd.h"

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
    return fprintf(f, "%s ", (char*)s);
}

int main(int argc, char ** argv) {
    ConfiguracionAp * p_cap;
    ConfiguracionAp * p_cap2;
    ConfiguracionAp * p_cap_aux;
    char texto[1024];
    ConfiguracionApnd * capnd;
    Stack * pila;
    Estado * estado;
    Palabra * cadena;
    capnd = configuracionApndIni();
    cadena = palabraNueva();
    palabraInsertaLetra(cadena, "a1");
    palabraInsertaLetra(cadena, "a2");
    palabraInsertaLetra(cadena, "a3");
    palabraInsertaLetra(cadena, "a4");
    pila = stack_ini(destroy_p_string, copy_p_string,
            print_p_string, (cmp_element_function_type) strcmp);
    sprintf(texto, "z");
    stack_push(pila, texto);
    sprintf(texto, "a");
    stack_push(pila, texto);
    sprintf(texto, "b");
    stack_push(pila, texto);
    estado = estadoNuevo("q1", 2);
    p_cap = configuracionApNueva(estado, pila, cadena);
    p_cap2 = configuracionApCopia(p_cap);
    /*Annadido*/
    printf ("COMPARACION: %d", configuracionCompara(p_cap, p_cap2));
    configuracionApndInsert(capnd, p_cap);
    configuracionApndInsert(capnd, p_cap2);
    fprintf(stdout, "\nCONFIGURACION 1\n");
    configuracionApImprime(stdout, p_cap);
    configuracionApElimina(p_cap);
    estadoElimina(estado);
    stack_destroy(pila);
    palabraElimina(cadena);
    fprintf(stdout, "\nCONFIGURACION 2\n");
    configuracionApImprime(stdout, p_cap2);
    configuracionApElimina(p_cap2);
    fprintf(stdout, "\nCONFIGURACION NO DETERMINISTA\n");
    configuracionApndPrint(stdout, capnd);
    printf("SIZE: %d\n", configuracionApndSize(capnd));
    fprintf(stdout, "\nCONFIGURACION NO DETERMINISTA, IMPRESA ELEMENTO A "
            "ELEMENTO\n");
    while (configuracionApndIsEmpty(capnd) != 1) {
        p_cap_aux = configuracionApndExtract(capnd);
        fprintf(stdout, "\nELEMENTO\t");
        configuracionApImprime(stdout, p_cap_aux);
        configuracionApElimina(p_cap_aux);
    }
    configuracionApndDestroy(capnd);
    return 0;
}
