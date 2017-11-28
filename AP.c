#include "AP.h"
#define SIMBOLO_INICIO_PILA 'Z'

struct _AP {
    char *nombre;
    List *alfabeto; /*Set*/
    int len_alfabeto;
    List *alfabeto_pila;/*Set*/
    int len_alfabeto_pila;
    List *estados; /*Set*/
    int len_estados;
    List *fn_transicion; /*Vamos a tratarlo como una lista de transiciones
                          * siendo transicion un TAD nuevo*/
    Relacion *lambdas;
    Palabra *palabra;
    ConfiguracionApnd *q;
};

/*fin funciones transicion*/
AP * APNuevo(char * nombre,
        int num_estados,
        int num_simbolos_entrada,
        int num_simbolos_pila);

void APElimina(AP * p_ap){
    if(p_ap->nombre)
        free(p_ap-> nombre);
    if(p_ap->alfabeto)
        list_destroy(p_ap->alfabeto);
    if(p_ap->estados)
        list_destroy(p_ap->estados);

    /*TODO DISTROY TRANSICIONES*/

    if(p_ap->lambdas)
        relacionElimina(p_ap->lambdas);
    if(p_ap->palabra)
        palabraElimina(p_ap->palabra);
    if(p_ap->q)
        configuracionApndDestroy(p_ap->q);

    free(p_ap);

}

void APImprime(FILE * fd, AP* p_ap);

AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo){
    /*no control de errores, asumimos el usuario sabe lo que hace*/

    if(list_belongs(p_Ap->alfabeto, (void *) simbolo))
        return p_ap;

    list_insertFirst(p_ap->alfabeto,(void *) simbolo);
    p_ap->len_alfabeto++:

}

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo){
    /*no control de errores, asumimos el usuario sabe lo que hace*/

    if(list_belongs(p_Ap->alfabeto_pila, (void *) simbolo))
        return p_ap;

    list_insertFirst(p_ap->alfabeto_pila,simbolo);
    p_ap->len_alfabeto_pila++:

}

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo){
    Estado e=NULL;

    e=estadoNuevo(nombre,tipo);
    if(!e)
        return NULL;

    if(list_belongs(p_Ap->estados, (void *) e)){
        estadoElimina(e);
        return p_ap;
    }
    list_insertFirst(p_ap->estados,e);
    p_ap->len_estados++:
}

AP * APInsertaLTransicion(AP * p_ap, char * nombre_estado_i,char * nombre_estado_f){

    int i=-1,j=-1,k;
    Relacion * p_r;

    for (k=0;k<p_ap->len_estados;k++){
        if(estadoEs(p_ap->estados[k],nombre_estado_i)
            i=k;
        if(estadoEs(p_ap->estados[k],nombre_estado_j)
            j=k;
        if(i!=-1 && j!=-1)
            break;
    }
    relacionInserta(p_ap->lambdas, i,  j);
}

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion);

AP * APInsertaLetra(AP * p_ap, char * letra){
    palabraInsertaLetra(p_ap->palabra,letra);
}

AP * APCierraLTransicion(AP * p_ap){
    relacionCierreTransitivo(p_ap->lambdas);
}

AP * APInicializaEstado(AP * p_ap){
    /*TODO*/
}

int APTransita(AP * p_ap);

int APProcesaEntrada(FILE *fd, AP * p_ap);
