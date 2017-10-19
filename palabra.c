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

Palabra * palabraNueva();

/* Crea una palabra nueva */
void palabraElimina(Palabra * p_p) {
    int i;

    if (!p_p) return;

    for (i = 0; i < p_p->tam; i++)
        free(p_p->word + i);

    free(p_p->word);

    free(p_p);
}
/* Libera la memoria asociada con la palabra */
void palabraImprime(FILE * fd, Palabra * p_p);

Palabra * palabraInsertaLetra(Palabra * p_p, char * letra) {
    int len;

    if (!p_p || !p_p->word || !letra) return NULL;

    len = strlen(letra);

    p_p->word = realloc(p_p->word, p_p->lon);

    p_p->word[p_p->lon] = (char*) malloc((len + 1) * sizeof (char));

    strcpy(p_p->word[p_p->lon], letra);

    p_p->lon++;
    p_p->tam += len;

    return p_p;
}
/* Inserta una letra (que es un string - char * - ) en la palabra proporcionada
como argumento (modificándola, por tanto) y devuelve la palabra resultante. Para
ello debe hacer una copia en memoria nueva para la nueva letra */

int palabraTamano(Palabra * p_p);
/* Devuelve la longitud de la palabra */

Palabra * palabraCopia(Palabra * p_p);
/* Hace en memoria nueva una copia de la palabra y la devuelve */

int palabraCompara(Palabra * p_p1, Palabra * p_p2);
/* Para comparar dos palabras, devuelve un valor negativo, cero o positivo en
función de que todas las letras de la misma posición y de izquierda a derecha
sean iguales. En el caso de que no lo sean, se devuelve el strcmp de la primera
pareja de letras que no sean iguales */
