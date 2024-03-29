#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palabra.h"

struct _Palabra {
    int lon; /*Tamano del array*/
    char **word;
};

Palabra * palabraNueva() {
    Palabra *p = NULL;

    p = (Palabra*) malloc(sizeof (Palabra));

    p->word = NULL;
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
    
    if(!fd || ! p_p) return;
    
    fprintf(fd, "[(%d)", p_p->lon);
    for (i = 0; i < p_p->lon; i++)
        fprintf(fd, "%s ", p_p->word[i]);
    fprintf(fd, "]");
}

Palabra * palabraInsertaLetra(Palabra * p_p, char * letra) {
    int len;

    if (!p_p || !letra) return NULL;

    len = strlen(letra);

    p_p->lon++;

    p_p->word = realloc(p_p->word, p_p->lon * sizeof(char*));

    p_p->word[p_p->lon - 1] = (char*) malloc((len + 1) * sizeof (char));

    strcpy(p_p->word[p_p->lon - 1], letra);


    return p_p;
}

char ** palabraGetPalabra(Palabra * p_p){
    return p_p->word;
    
}
/* Inserta una letra (que es un string - char * - ) en la palabra proporcionada
como argumento (modificándola, por tanto) y devuelve la palabra resultante. Para
ello debe hacer una copia en memoria nueva para la nueva letra */

int palabraTamano(Palabra * p_p) {
    return p_p->lon;
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

    v = p_p1->lon - p_p2->lon;

    if (v)
        return v;

    for (i = 0; i < p_p1->lon; i++) {
        v = strcmp(p_p1->word[i], p_p2->word[i]);
        if (!v)
            return v;
    }
    return 0;

}
