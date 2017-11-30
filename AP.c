#include "AP.h"
#include "list.h"
#include "estado.h"
#include "palabra.h"
#include "stack.h"
#include <string.h>
#include <stdio.h>
#define SIMBOLO_INICIO_PILA 'Z'

/*funciones de transicion*/
struct _transicionAP {
    List* ****acciones;
    int num_simbolos_pila;
    int num_estados;
    int num_simbolos_entrada;
};

typedef struct _transicionAP TransicionAP;

struct _AP {
    char *nombre;
    List *alfabeto; /*Set*/
    int len_alfabeto;
    List *alfabeto_pila;
    int len_alfabeto_pila;
    List *estados; /*Set*/
    int len_estados;
    Relacion *lambdas;
    Palabra *palabra;
    ConfiguracionApnd *q;
    TransicionAP * fn_tansicion;
    Stack *pila;
};


void *copy_p_string(const void* s1){
    char *s2;
    
    s2 = (char*)malloc(sizeof(char)* strlen((char*)s1)+1);
    
    strcpy(s2, (char*)s1);
    
    return s2;
    
}
int print_p_string(FILE *f, const void*s){
    return fprintf(f, "%s ", (char*)s);
}

TransicionAP *transicionAPNueva(char * nombre, int num_simbolos_pila,
        int num_estados, int num_simbolos_entrada) {
    TransicionAP *t;
    int pila, estado_ini, estado_fin, entrada;

    if (!nombre) return NULL;

    t = (TransicionAP *) malloc(sizeof (TransicionAP));
    if (!t) return NULL;

    t->num_simbolos_pila = num_simbolos_pila;
    t->num_estados = num_estados;
    t->num_simbolos_entrada = num_simbolos_entrada;

    t->acciones = (List* ****) malloc(num_simbolos_pila * sizeof (List ****));
    for (pila = 0; pila < num_simbolos_pila; pila++) {
        t->acciones[pila] = (List ****) malloc(num_estados * sizeof (List***));
        for (estado_ini = 0; estado_ini < num_estados; estado_ini++) {
            t->acciones[pila][estado_ini] = (List ***) malloc(num_simbolos_entrada * sizeof (List**));
            for (estado_fin = 0; estado_fin < num_estados; estado_fin++) {
                t->acciones[pila][estado_ini][estado_fin] = (List **) malloc(num_simbolos_entrada * sizeof (List*));
                for (entrada = 0; entrada < num_simbolos_entrada; entrada++)
                    t->acciones[pila][estado_ini][estado_fin][entrada] = 
                            list_ini((destroy_element_function_type)palabraElimina,
                            (copy_element_function_type) palabraCopia,
                            (print_element_function_type) palabraImprime,
                            (cmp_element_function_type) palabraCompara);
            }
        }
    }
    return t;
}

void transicionAPLibera(TransicionAP *t) {
    int pila, estado_ini, estado_fin, entrada;
    if (!t) return;

    for (pila = 0; pila < t->num_simbolos_pila; pila++) {
        for (estado_ini = 0; estado_ini < t->num_estados; estado_ini++) {
            for (estado_fin = 0; estado_fin < t->num_estados; estado_fin++) {
                for (entrada = 0; entrada < t->num_simbolos_entrada; entrada++)
                    list_destroy(t->acciones[pila][estado_ini][estado_fin][entrada]);
                free(t->acciones[pila][estado_ini][estado_fin]);
            }
            free(t->acciones[pila][estado_ini]);
        }
        free(t->acciones[pila]);
    }
    free(t->acciones);
    free(t);
}

TransicionAP *transicionAPinserta(TransicionAP *t, int pila, int estado_ini,
        int estado_fin, int entrada, Palabra* palabra) {
    if (!t || !palabra) return NULL;
    if (pila >= t->num_simbolos_pila || estado_ini >= t->num_estados ||
            estado_fin >= t->num_estados || entrada >= t->num_simbolos_entrada)
        return NULL;
    list_insertFirst(t->acciones[pila][estado_ini][estado_fin][entrada], (void*)palabra);

    return t;

}

List *transicionAPbusca(TransicionAP *t, int pila, int estado_ini,
        int estado_fin, int entrada){
    if(pila > t->num_simbolos_pila || estado_ini > t->num_estados || 
            estado_fin > t->num_estados || entrada > t->num_simbolos_entrada)
        return NULL;
    return t->acciones[pila][estado_ini][estado_fin][entrada];
}

/*fin funciones transicion*/
AP * APNuevo(char * nombre,
        int num_estados,
        int num_simbolos_entrada,
        int num_simbolos_pila) {
    AP *ap;

    ap = (AP*) malloc(sizeof (AP));
    if (!ap) return NULL;

    ap->nombre = (char*) malloc((strlen(nombre) + 1) * sizeof (char));
    if(!ap->nombre) return NULL;
    strcpy(ap->nombre, nombre);
    
    ap->alfabeto = list_ini((destroy_element_function_type)free, copy_p_string, 
    print_p_string, (cmp_element_function_type)strcmp);
    
    ap->estados = list_ini((destroy_element_function_type)estadoElimina, 
    (copy_element_function_type)estado_copy, (print_element_function_type)estadoImprime, 
    (cmp_element_function_type)estadoCompara);

    ap->alfabeto_pila = list_ini((destroy_element_function_type)free, copy_p_string, 
    print_p_string, (cmp_element_function_type)strcmp);
    
    ap->lambdas = relacionNueva(nombre, num_estados);
    ap->palabra = palabraNueva();
    ap->q = configuracionApndIni();
    ap->fn_tansicion = transicionAPNueva(nombre, num_simbolos_pila,
        num_estados, num_simbolos_entrada);
    
    ap->len_alfabeto_pila = num_simbolos_pila;
    ap->len_alfabeto = num_simbolos_entrada;
    ap->len_estados = num_estados;
    
    ap->pila = stack_ini((destroy_element_function_type)free, copy_p_string, 
    print_p_string, (cmp_element_function_type)strcmp);
    
    ap->fn_tansicion = transicionAPNueva(nombre, num_simbolos_pila, num_estados, 
    num_simbolos_entrada);
    
    return ap;
}

void APElimina(AP * p_ap);

void APImprime(FILE * fd, AP * p_ap);

AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo);

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo);

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo);

AP * APInsertaLTransicion(AP * p_ap,
        char * nombre_estado_i,
        char * nombre_estado_f);

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion);

AP * APInsertaLetra(AP * p_ap, char * letra);

AP * APCierraLTransicion(AP * p_ap);

AP * APInicializaEstado(AP * p_ap);

int APTransita(AP * p_ap);

int APProcesaEntrada(FILE *fd, AP * p_ap);