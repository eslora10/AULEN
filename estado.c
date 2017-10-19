#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estado.h"

struct _Estado{
    char* nombre;
    int tipo;    
};

Estado * estadoNuevo( char * nombre, int tipo){
    Estado *estado = NULL;
    
    if(!nombre) return NULL;
    
    estado = (Estado*)malloc(sizeof(Estado));
    
    estado->nombre = (char*)malloc((strlen(nombre)+1)*sizeof(char));
    strcpy(estado->nombre, nombre);
      
    estado->tipo = tipo;
    
    return estado;
}
/* Reserva memoria nueva para el estado y para la cadena de su nombre, crea un
estado con las dos componentes que se le proporcionan como argumento */
void estadoElimina( Estado * p_s);
/* Libera la memoria asociada con el estado */
void estadoImprime( FILE * fd, Estado * p_s){
    if(!fd || !p_s) return;
    
    switch(p_s->tipo){
        case INICIAL:
            break;
        case FINAL:
            break;
        case INICIAL_Y_FINAL: 
            break;
        default:
            break;
            
    }
}
/* Muestra por el FILE * el estado */
int estadoEs(Estado * p_s, char * nombre);
/* Función de comparación de estados por nombre, devuelve 1 si el estado tiene el
nombre proporcionado */
char * estadoNombre(Estado * p_s);
/* Devuelve (un puntero) al nombre del estado */
int estadoTipo(Estado * p_s);
/* Devuelve el tipo de estado */
int estadoCompara(Estado * p_s1, Estado * p_s2);
/* Se usa para comparar estados por su nombre y devuelve el strcmp de sus nombres
*/
Estado * estado_copy(Estado * p_s);
/* Se crea una copia en memoria nueva del estado proporcionado como argumento */
