#include "relacion.h"

struct _Relacion {
    char *nombre;
    int num_elementos;
    int **origen;
    int **cierre;
};

Relacion * relacionNueva(char * nombre, int num_elementos){
  Relacion *r = NULL;
  int i=0;

  r = (Relacion*) malloc(sizeof (Relacion));

  r->nombre = nombre;
  r->num_elementos = num_elementos;

/*init elem*/
  r->origen = (int**) malloc(num_elementos*sizeof (int*));
  for (i=0;i<num_elementos;i++)
    r->origen[i] = (int*) calloc(num_elementos,sizeof (int));

/*init cierre*/
  r->cierre = (int**) malloc(num_elementos*sizeof (int*));
  for (i=0;i<num_elementos;i++)
    r->cierre[i] = (int*) calloc(num_elementos,sizeof (int));

  return r;


}

void relacionImprime(FILE * fd, Relacion * p_r);
/*
Muestra por el FILE * la relación. Puedes suponer el formato de salida utilizado en los ejemplos.
 */
void relacionElimina(Relacion * p_r){

  int i=0;

  if (!p_r) return;

  for (i = p_r->num_elementos; i >0; i--){
    free(p_r->origen[i]);
    free(p_r->cierre[i]);
  }

  free(p_r->origen);
  free(p_r->cierre);

  if(p_r->nombre)
    free(p_r->nombre);

}

Relacion * relacionCopia(Relacion * p_r1);
/*
Genera en memoria nueva una copia de la relación proporcionada como argumento y la devuelve.
 */
Relacion * relacionInserta(Relacion * p_r, int i, int j){
  p_r->origen[i][j]=1;
  p_r->cierre[i][j]=1;
  return p_r;
}


int relacionTamano(Relacion * p_r);
/*
Devuelve el cardinal del conjunto sobre el que está definida la relación.
 */

Relacion * relacionCierreTransitivo(Relacion * p_r);

/*
Modifica la relación para conservar el ella su cierre transitivo. Devuelve la relación como retorno.
 */
int relacionIJ(Relacion * p_r, int i, int j);
/*
Devuelve 1 si el elemento i está relacionado originalmente con el j y 0 en caso contrario.
 */
int relacionCierreIJ(Relacion * p_r, int i, int j){
  /*indices positivos, principio RTFM*/
  return p_r->cierre[i][j];
}
