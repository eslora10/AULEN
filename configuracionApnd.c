#include "configuracionApnd.h"
#include "list.h"

struct _ConfiguracionApnd{
    List *set;    
};

ConfiguracionApnd * configuracionApndIni( ){
    ConfiguracionApnd *capnd;
    
    capnd = (ConfiguracionApnd*)malloc(sizeof(ConfiguracionApnd));
    
    if(!capnd) return NULL;
    
    /*Los elementos de la configuracionApnd son configuraciones ap por tanto 
     utilizamos las funciones definidas*/
    capnd->set = list_ini((destroy_element_function_type)configuracionApElimina, 
    (copy_element_function_type)configuracionApCopia,
    (print_element_function_type)configuracionApImprime, 
    (cmp_element_function_type)configuracionCompara);
    
    return capnd;
}

ConfiguracionApnd* configuracionApndInsert(ConfiguracionApnd* capnd, const
ConfiguracionAp * p_cap);
/* Inserta una configuración determinista en una no determinista. Se realiza una
copia en memoria propia de la colección para el nuevo elemento y se asegura que
no haya duplicados*/
ConfiguracionAp * configuracionApndExtract(ConfiguracionApnd * capnd){
    if(!capnd) return NULL;
    /*No compruebo que la lista no sea vacia porque ya se hace en list*/
    
    return (ConfiguracionAp*)list_extractFirst(capnd->set);
        
}
/* Se obtiene una configuración determinista de la no determinista, que
desaparece de la colección.
No se especifica el orden en el que se extrae */
int configuracionApndIsEmpty(const ConfiguracionApnd* capnd);
/* Se devuelve 1 si está vacía y 0 en caso contrario */
int configuracionApndSize(const ConfiguracionApnd * capnd);
/* Se devuelve el número de configuraciones deterministas que hay dentro de la no
determinista */
int configuracionApndPrint(FILE *fd, const ConfiguracionApnd* capnd);
/* Se imprime todas las configuraciones deterministas. No se especifica en qué
orden */
void configuracionApndDestroy( ConfiguracionApnd* capnd);
/* Se libera toda la memoria asociada con la configuracion no determinista */
