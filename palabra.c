#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palabra.h"

struct _Palabra {
    int tam; /*Tamano de la palabra entendido como la suma de la longitud
              * de las cadenas que contiene*/
    int lon; /*Tamano del array*/
    char **word;
};

Palabra * palabraNueva() {
    Palabra *p = NULL;

    p = (Palabra*) malloc(sizeof (Palabra));
    
    p->word = NULL;
    p->tam = 0;
    p->lon = 0;
    return p;
}

/* Crea una palabra nueva */
void palabraElimina(Palabra * p_p) {
    int i;

    if (!p_p) return;

    for (i = 0; i < p_p->lon; i++)
        free(p_p->word[i]);

    free(p_p->word);

    free(p_p);
}

/* Libera la memoria asociada con la palabra */
void palabraImprime(FILE * fd, Palabra * p_p) {
    int i;

    for (i = 0; i < p_p->lon; i++)
        fprintf(fd, "%s", p_p->word[i]);
}

Palabra * palabraInsertaLetra(Palabra * p_p, char * letra) {
    int len;

    if (!p_p || !letra) return NULL;

    len = strlen(letra);

    p_p->lon++;

    p_p->word = realloc(p_p->word, p_p->lon * sizeof(char*));

    p_p->word[p_p->lon - 1] = (char*) malloc((len + 1) * sizeof (char));

    strcpy(p_p->word[p_p->lon - 1], letra);

    p_p->tam += len;

    return p_p;
}

/* Inserta una letra (que es un string - char * - ) en la palabra proporcionada
como argumento (modificándola, por tanto) y devuelve la palabra resultante. Para
ello debe hacer una copia en memoria nueva para la nueva letra */

int palabraTamano(Palabra * p_p) {
    return p_p->tam;
}

Palabra * palabraCopia(Palabra * p_p) {
    Palabra *p = NULL;
    int i;

    if (!p_p) return NULL;

    p = palabraNueva();

    for (i = 0; i < p_p->lon; i++) {
        palabraInsertaLetra(p, p_p->word[i]);
    }

    return p;
}

int palabraCompara(Palabra * p_p1, Palabra * p_p2) {
    int v, i;

    if (!p_p1 || !p_p2) return -1;

    v = p_p1->tam - p_p2->tam;

    if (v)
        return -1;

    for (i = 0; i < p_p1->tam; i++) {
        v = strcmp(p_p1->word[i], p_p2->word[i]);
        if (!v)
            return v;
    }
    return 0;

}
