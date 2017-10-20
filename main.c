#include <string.h>
#include <stdio.h>
#include "estado.h"
#include "palabra.h"

int main(int argc, char ** argv) {
    Palabra *p1, *p2;

    p1 = palabraNueva();

    palabraInsertaLetra(p1, "a1");
    palabraInsertaLetra(p1, "a2");
    palabraInsertaLetra(p1, "a3");
    palabraInsertaLetra(p1, "a4");
    
    p2 = palabraCopia(p1);


    palabraImprime(stdout, p1);
    printf("\n");
    palabraImprime(stdout, p2);
    printf("\n");
    
    
    printf("Comparación: %d\n", palabraCompara(p1, p2));

    palabraElimina(p1);
    palabraElimina(p2);

    return 0;
}