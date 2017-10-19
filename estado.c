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

    if (!nombre) return NULL;

    estado = (Estado*) malloc(sizeof (Estado));

    estado->nombre = (char*) malloc((strlen(nombre) + 1) * sizeof (char));
    strcpy(estado->nombre, nombre);

    estado->tipo = tipo;

    return estado;
}
/* Reserva memoria nueva para el estado y para la cadena de su nombre, crea un
estado con las dos componentes que se le proporcionan como argumento */

void estadoImprime(FILE * fd, Estado * p_s) {
    if (!fd || !p_s) return;

    switch (p_s->tipo) {

        case INICIAL:
            fprintf(fd, "->%s", p_s->nombre);
            break;
        case FINAL:
            fprintf(fd, "%s*", p_s->nombre);
            break;
        case INICIAL_Y_FINAL:
            fprintf(fd, "->%s*\n", p_s->nombre);
            break;
        default:
            fprintf(fd, "%s\n", p_s->nombre);
            break;
    }
}
/* Muestra por el FILE * el estado */
int estadoEs(Estado * p_s, char * nombre){
  if(strcmp(p_s->nombre,nombre)){
    return 1;
  }else
    return 0;
}

char * estadoNombre(Estado * p_s) {
    if (!p_s) return NULL;

    return p_s->nombre;
}

int estadoTipo(Estado * p_s){
  return p_s->tipo;
}
int estadoCompara(Estado * p_s1, Estado * p_s2) {
    if (!p_s1 || !p_s2) return -1;

    return strcmp(p_s1->nombre, p_s2->nombre);
}
Estado * estado_copy(Estado * p_s){
  Estado *estado = NULL;

  if (!p_s) return NULL;

  estado = (Estado*)malloc(sizeof(Estado));

  estado->nombre = (char*)malloc((strlen(p_s->nombre)+1)*sizeof(char));
  strcpy(estado->nombre, p_s->nombre);

  estado->tipo = p_s->tipo;

  return estado;
}
