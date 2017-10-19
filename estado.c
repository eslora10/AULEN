#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estado.h"

struct _Estado {
    char* nombre;
    int tipo;
};

Estado * estadoNuevo(char * nombre, int tipo) {
    Estado *estado = NULL;

<<<<<<< HEAD
    if(!nombre) return NULL;

    estado = (Estado*)malloc(sizeof(Estado));

    estado->nombre = (char*)malloc((strlen(nombre)+1)*sizeof(char));
=======
    if (!nombre) return NULL;

    estado = (Estado*) malloc(sizeof (Estado));

    estado->nombre = (char*) malloc((strlen(nombre) + 1) * sizeof (char));
>>>>>>> 80aab41be873e9cf5870882dd9a7502bc2867982
    strcpy(estado->nombre, nombre);

    estado->tipo = tipo;

    return estado;
}
/* Reserva memoria nueva para el estado y para la cadena de su nombre, crea un
estado con las dos componentes que se le proporcionan como argumento */
<<<<<<< HEAD
void estadoElimina( Estado * p_s){
    free(estado->nombre);
    estado->nombre=NULL;
    free(p_s);
}
/* Libera la memoria asociada con el estado */
void estadoImprime( FILE * fd, Estado * p_s){
    if(!fd || !p_s) return;

    switch(p_s->tipo){
=======
void estadoElimina(Estado * p_s);

/* Libera la memoria asociada con el estado */
void estadoImprime(FILE * fd, Estado * p_s) {
    if (!fd || !p_s) return;

    switch (p_s->tipo) {
>>>>>>> 80aab41be873e9cf5870882dd9a7502bc2867982
        case INICIAL:
            fprintf(fd, "->%s", p_s->nombre);
            break;
        case FINAL:
            fprintf(fd, "%s*", p_s->nombre);
            break;
        case INICIAL_Y_FINAL:
<<<<<<< HEAD
=======
            fprintf(fd, "->%s*\n", p_s->nombre);
>>>>>>> 80aab41be873e9cf5870882dd9a7502bc2867982
            break;
        default:
            fprintf(fd, "%s\n", p_s->nombre);
            break;
<<<<<<< HEAD

    }
}
/* Muestra por el FILE * el estado */
int estadoEs(Estado * p_s, char * nombre){
  if(strcmp(p_s->nombre,nombre)){
    return 1;
  }else
    return 0;
}
char * estadoNombre(Estado * p_s);
/* Devuelve (un puntero) al nombre del estado */
int estadoTipo(Estado * p_s){
  return p_s->tipo;
}
int estadoCompara(Estado * p_s1, Estado * p_s2);
/* Se usa para comparar estados por su nombre y devuelve el strcmp de sus nombres
*/
Estado * estado_copy(Estado * p_s){
  Estado *estado = NULL;

  if (!p_s) return NULL;

  estado = (Estado*)malloc(sizeof(Estado));

  estado->nombre = (char*)malloc((strlen(p_s->nombre)+1)*sizeof(char));
  strcpy(estado->nombre, p_s->nombre);

  estado->tipo = p_s->tipo;

  return estado;
}
=======
    }
}
/* Muestra por el FILE * el estado */
int estadoEs(Estado * p_s, char * nombre);

/* Función de comparación de estados por nombre, devuelve 1 si el estado tiene el
nombre proporcionado */
char * estadoNombre(Estado * p_s) {
    if (!p_s) return NULL;

    return p_s->nombre;
}
/* Devuelve (un puntero) al nombre del estado */
int estadoTipo(Estado * p_s);

/* Devuelve el tipo de estado */
int estadoCompara(Estado * p_s1, Estado * p_s2) {
    if (!p_s1 || !p_s2) return -1;
    
    return strcmp(p_s1->nombre, p_s2->nombre);
}
/* Se usa para comparar estados por su nombre y devuelve el strcmp de sus nombres
 */
Estado * estado_copy(Estado * p_s);
/* Se crea una copia en memoria nueva del estado proporcionado como argumento */
>>>>>>> 80aab41be873e9cf5870882dd9a7502bc2867982
