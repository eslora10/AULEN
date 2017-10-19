#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palabra.h"

struct _Palabra {
    int tam;
    char **word;
};

Palabra * palabraNueva(){
    Palabra p=NULL;

      p = (Palabra*) malloc(sizeof (Palabra));

      p->tam=0;
      /*p->lon=0;*/
      p->word=NULL;
      return p;
}
void palabraElimina(Palabra * p_p);
/* Libera la memoria asociada con la palabra */
void palabraImprime(FILE * fd, Palabra * p_p){
  for(int i=0;i<p_p->tam;i++)
    fprintf(fd, "%s\n",p_p->word[i] );
}

Palabra * palabraInsertaLetra(Palabra * p_p, char * letra);
/* Inserta una letra (que es un string - char * - ) en la palabra proporcionada
como argumento (modificándola, por tanto) y devuelve la palabra resultante. Para
ello debe hacer una copia en memoria nueva para la nueva letra */

int palabraTamano(Palabra * p_p){
  return p_p->tam;
}

Palabra * palabraCopia(Palabra * p_p);

  if (!p_p) return NULL;
  p = (Palabra*) malloc(sizeof (Palabra));

  for(int i=0;i< p_p->tam ;i++){
    palabraInsertaLetra(p,p_p->word[i]);
  }
  p->tam=p_p->tam;
  /*p->lon=p_p->lon;*/

  return p;

int palabraCompara(Palabra * p_p1, Palabra * p_p2){
/* Para comparar dos palabras, devuelve un valor negativo, cero o positivo en
función de que todas las letras de la misma posición y de izquierda a derecha
sean iguales. En el caso de que no lo sean, se devuelve el strcmp de la primera
pareja de letras que no sean iguales */
  int v=p_p1->tam-p_p2->tam;
  if (!v)
    return -1;

  for(int i=0;i<p_p->tam;i++){
    v=strcmp(p_p1->word[i], p_p2->word[i])
    if(!v)
      return v;
    }
  return 0;

}
