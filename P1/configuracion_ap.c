#include "configuracion_ap.h"

struct _ConfiguracionAp {
    Estado *estado;
    Stack *pila;
    Palabra *cadena;

};

ConfiguracionAp * configuracionApNueva(Estado * estado, Stack * pila, Palabra *
        cadena) {
    ConfiguracionAp *c = NULL;

    c = (ConfiguracionAp*) malloc(sizeof (ConfiguracionAp));

    if (!c)
        return NULL;

    c->estado = estado_copy(estado);
    c->cadena = palabraCopia(cadena);
    c->pila = stack_copy(pila);

    return c;
}

void configuracionApElimina(ConfiguracionAp * p_cap) {
    if (!p_cap) return;

    if (p_cap->estado)
        estadoElimina(p_cap->estado);

    if (p_cap->pila)
        stack_destroy(p_cap->pila);

    if (p_cap->cadena)
        palabraElimina(p_cap->cadena);

    free(p_cap);
}

Estado *getEstado(ConfiguracionAp * p_cap) {
    return p_cap->estado;
}

Stack *getPila(ConfiguracionAp * p_cap) {
    return p_cap->pila;
}

Palabra *getCadena(ConfiguracionAp * p_cap) {
    return p_cap->cadena;
}

void configuracionApImprime(FILE * fd, ConfiguracionAp * p_cap) {

    fprintf(fd, "(");
    estadoImprime(fd, p_cap->estado);
    stack_print(fd, p_cap->pila);
    palabraImprime(fd, p_cap->cadena);
    fprintf(fd, ")\n");

}

ConfiguracionAp * configuracionApCopia(ConfiguracionAp * p_cap) {
    ConfiguracionAp *newp_cap = NULL;

    if (!p_cap) return NULL;

    newp_cap = configuracionApNueva(p_cap->estado, p_cap->pila, p_cap->cadena);
    if (!newp_cap) return NULL;

    /*
    newp_cap->estado = estado_copy(p_cap->estado);
    newp_cap->cadena = palabraCopia(p_cap->cadena);
    newp_cap->pila = stack_copy(p_cap);
     */

    return newp_cap;
}

int configuracionCompara(ConfiguracionAp * p_cap1, ConfiguracionAp * p_cap2) {
    int ret;

    if (!p_cap1 || !p_cap2) return -1;

    /*Comparar estados*/
    ret = estadoCompara(p_cap1->estado, p_cap2->estado);

    if (ret) return ret;

    /*Comparar pilas*/
    ret = stack_compare(p_cap1->pila, p_cap2->pila);

    if (ret) return ret;

    /*Comparar cadenas*/
    ret = palabraCompara(p_cap1->cadena, p_cap2->cadena);

    return ret;

}
