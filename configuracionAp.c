#include "configuracionAp.h"

struct _ConfiguracionAp {
    Estado *estado;
    Stack *pila;
    Palabra *cadena;

};

ConfiguracionAp * configuracionApNueva(Estado * estado, Stack * pila, Palabra *
        cadena){
    ConfiguracionAp *c=NULL;

    c = (ConfiguracionAp*) malloc(sizeof (ConfiguracionAp));

    if (!c)
        return NULL;

    /*c->estado=estado;
    c->pila=pila;
    c->cadena=stack_copy(cadena;*/

    return c;
        }
/* Se crea una configuración reservando memoria nueva para ella y para copiar
todas las componentes que se proporcionan como argumento */
void configuracionApElimina(ConfiguracionAp * p_cap);
/* Se libera toda la memoria asociada con la configuracion */
void configuracionApImprime(FILE * fd, ConfiguracionAp * p_cap){

  fprintf(fd, "( ");
  estadoImprime(fd,p_cap->estado);
  stack_print(fd, p_cap->pila);
  palabraImprime(fd,p_cap->cadena);
  fprintf(fd, " )\n");

}
/* Se muestra por pantalla la configuración */
ConfiguracionAp * configuracionApCopia(ConfiguracionAp * p_cap);
/* Se devuelve una copia en memoria nueva de la configuración */
int configuracionCompara(ConfiguracionAp * p_cap1, ConfiguracionAp * p_cap2);
/* Se utiliza para comparar dos configuraciones deterministas, devolviendo un
valor negativo, 0 o positivo en función de la comparación de sus componentes en
este orden: estados, pilas, cadenas. En el caso de que no sean iguales, devuelve
el valor que devuelva la comparación de la primera que sea distinta*/
