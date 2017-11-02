#ifndef CONFIGURACIONAPND_H
#define CONFIGURACIONAPND_H

#include "configuracion_ap.h"

typedef struct _ConfiguracionApnd ConfiguracionApnd;

ConfiguracionApnd * configuracionApndIni( );
/* Inicializa una configuración no determinista */
ConfiguracionApnd* configuracionApndInsert(ConfiguracionApnd* capnd, const
ConfiguracionAp * p_cap);
/* Inserta una configuración determinista en una no determinista. Se realiza una
copia en memoria propia de la colección para el nuevo elemento y se asegura que
no haya duplicados*/
ConfiguracionAp * configuracionApndExtract(ConfiguracionApnd * capnd);
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

#endif